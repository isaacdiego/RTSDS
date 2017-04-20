/*******************************************************************************
* File Name: MAD_2.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the Successive
*  approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "MAD_2.h"

#if(MAD_2_DEFAULT_INTERNAL_CLK)
    #include "MAD_2_theACLK.h"
#endif /* End MAD_2_DEFAULT_INTERNAL_CLK */


/***************************************
* Forward function references
***************************************/
static void MAD_2_CalcGain(uint8 resolution);


/***************************************
* Global data allocation
***************************************/
uint8 MAD_2_initVar = 0u;
volatile int16 MAD_2_offset;
volatile int16 MAD_2_countsPerVolt;   /* Gain compensation */
volatile int16 MAD_2_shift;


/***************************************
* Local data allocation
***************************************/
#if(CY_PSOC5A)
    static uint8 MAD_2_resolution;
#endif /* End CY_PSOC5A */


/*******************************************************************************
* Function Name: MAD_2_Start
********************************************************************************
*
* Summary:
*  Performs all required initialization for this component and enables the
*  power.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The MAD_2_initVar variable is used to indicate when/if initial
*  configuration of this component has happened. The variable is initialized to
*  zero and set to 1 the first time ADC_Start() is called. This allows for
*  component Re-Start without re-initialization in all subsequent calls to the
*  MAD_2_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of MAD_2_Start() routine, or the user may call
*  MAD_2_Init() and MAD_2_Enable() as done in the
*  MAD_2_Start() routine.
*
*******************************************************************************/
void MAD_2_Start(void)
{

    /* If not Initialized then initialize all required hardware and software */
    if(MAD_2_initVar == 0u)
    {
        MAD_2_Init();
        MAD_2_initVar = 1u;
    }
    MAD_2_Enable();
}


/*******************************************************************************
* Function Name: MAD_2_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  MAD_2_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The MAD_2_offset variable is initialized to 0.
*
*******************************************************************************/
void MAD_2_Init(void)
{

    /* This is only valid if there is an internal clock */
    #if(MAD_2_DEFAULT_INTERNAL_CLK)
        MAD_2_theACLK_SetMode(CYCLK_DUTY);
    #endif /* End MAD_2_DEFAULT_INTERNAL_CLK */

    #if(MAD_2_IRQ_REMOVE == 0u)
        /* Start and set interrupt vector */
        CyIntSetPriority(MAD_2_INTC_NUMBER, MAD_2_INTC_PRIOR_NUMBER);
        (void)CyIntSetVector(MAD_2_INTC_NUMBER, &MAD_2_ISR);
    #endif   /* End MAD_2_IRQ_REMOVE */        

    /* Enable IRQ mode*/
    MAD_2_SAR_CSR1_REG |= MAD_2_SAR_IRQ_MASK_EN | MAD_2_SAR_IRQ_MODE_EDGE;

    /*Set SAR ADC resolution ADC */
    MAD_2_SetResolution(MAD_2_DEFAULT_RESOLUTION);
    MAD_2_offset = 0;
}


/*******************************************************************************
* Function Name: MAD_2_Enable
********************************************************************************
*
* Summary:
*  Enables the reference, clock and power for SAR ADC.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MAD_2_Enable(void)
{
    uint8 tmpReg;
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Enable the SAR ADC block in Active Power Mode */
    MAD_2_PWRMGR_SAR_REG |= MAD_2_ACT_PWR_SAR_EN;

     /* Enable the SAR ADC in Standby Power Mode*/
    MAD_2_STBY_PWRMGR_SAR_REG |= MAD_2_STBY_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(MAD_2_DEFAULT_INTERNAL_CLK)
        MAD_2_PWRMGR_CLK_REG |= MAD_2_ACT_PWR_CLK_EN;
        MAD_2_STBY_PWRMGR_CLK_REG |= MAD_2_STBY_PWR_CLK_EN;
    #endif /* End MAD_2_DEFAULT_INTERNAL_CLK */

    /* Enable VCM buffer and Enable Int Ref Amp */
    tmpReg = MAD_2_SAR_CSR3_REG;
    #if(CY_PSOC5A) /* Make sure that full power is applied for VREF buffer */
        tmpReg &= (uint8)~MAD_2_SAR_PWR_CTRL_VREF_DIV_BY4;
    #endif /* CY_PSOC5A */
    tmpReg |= MAD_2_SAR_EN_BUF_VCM_EN;
    /* PD_BUF_VREF is OFF in External reference or Vdda reference mode */
    #if((MAD_2_DEFAULT_REFERENCE == MAD_2__EXT_REF) || \
        (MAD_2_DEFAULT_RANGE == MAD_2__VNEG_VDDA_DIFF))
        tmpReg &= (uint8)~MAD_2_SAR_EN_BUF_VREF_EN;
    #else /* In INTREF or INTREF Bypassed this buffer is ON */
        tmpReg |= MAD_2_SAR_EN_BUF_VREF_EN;
    #endif /* MAD_2_DEFAULT_REFERENCE == MAD_2__EXT_REF */
    MAD_2_SAR_CSR3_REG = tmpReg;

    /* Set reference for ADC */
    #if(MAD_2_DEFAULT_RANGE == MAD_2__VNEG_VDDA_DIFF)
        #if(MAD_2_DEFAULT_REFERENCE == MAD_2__EXT_REF)
            MAD_2_SAR_CSR6_REG = MAD_2_INT_BYPASS_EXT_VREF; /* S2 */
        #else /* Internal Vdda reference or obsolete bypass mode */
            MAD_2_SAR_CSR6_REG = MAD_2_VDDA_VREF;           /* S7 */
        #endif /* MAD_2_DEFAULT_REFERENCE == MAD_2__EXT_REF */
    #else  /* Reference goes through internal buffer */
        #if(MAD_2_DEFAULT_REFERENCE == MAD_2__INT_REF_NOT_BYPASSED)
            MAD_2_SAR_CSR6_REG = MAD_2_INT_VREF;            /* S3 + S4 */
        #else /* INTREF Bypassed of External */
            MAD_2_SAR_CSR6_REG = MAD_2_INT_BYPASS_EXT_VREF; /* S2 */
        #endif /* MAD_2_DEFAULT_REFERENCE == MAD_2__INT_REF_NOT_BYPASSED */
    #endif /* VNEG_VDDA_DIFF */

    /* Low non-overlap delay for sampling clock signals (for 1MSPS) */
    #if(MAD_2_HIGH_POWER_PULSE == 0u) /* MinPulseWidth <= 50 ns */
        MAD_2_SAR_CSR5_REG &= (uint8)~MAD_2_SAR_DLY_INC;
    #else /* Set High non-overlap delay for sampling clock signals (for <500KSPS)*/
        MAD_2_SAR_CSR5_REG |= MAD_2_SAR_DLY_INC;
    #endif /* MAD_2_CLOCK_FREQUENCY > (MAD_2_MAX_FREQUENCY / 2) */

     /* Delay control for comparator latch enable, low delay, (Default for 1MSPS) */
    #if(MAD_2_HIGH_POWER_PULSE == 0u) /* MinPulseWidth <= 50 ns */
        MAD_2_SAR_CSR5_REG |= MAD_2_SAR_DCEN;
    #else /* Delay control for comparator latch enable, high delay (for <500ksps)*/
        MAD_2_SAR_CSR5_REG &= (uint8)~MAD_2_SAR_DCEN;
    #endif /* MAD_2_CLOCK_FREQUENCY > (MAD_2_MAX_FREQUENCY / 2) */

    /* Set default power and other configurations for control register 0 in multiple lines */
    MAD_2_SAR_CSR0_REG = (uint8)((uint8)MAD_2_DEFAULT_POWER << MAD_2_SAR_POWER_SHIFT)
    /* SAR_HIZ_CLEAR:   Should not be used for LP */
    #if ((CY_PSOC5LP) || (MAD_2_DEFAULT_REFERENCE != MAD_2__EXT_REF))
        | MAD_2_SAR_HIZ_CLEAR
    #endif /* SAR_HIZ_CLEAR */
    /*Set Convertion mode */
    #if(MAD_2_DEFAULT_CONV_MODE != MAD_2__FREE_RUNNING)      /* If triggered mode */
        | MAD_2_SAR_MX_SOF_UDB           /* source: UDB */
        | MAD_2_SAR_SOF_MODE_EDGE        /* Set edge-sensitive sof source */
    #endif /* MAD_2_DEFAULT_CONV_MODE */
    ; /* end of multiple line initialization */

    /* Enable clock for SAR ADC*/
    MAD_2_SAR_CLK_REG |= MAD_2_SAR_MX_CLK_EN;

    #if(CY_PSOC5A)
        /* Software Reset */
        MAD_2_SAR_CSR0_REG |= MAD_2_SAR_RESET_SOFT_ACTIVE;
        CyDelayUs(2u); /* 2us delay is required for the lowest 1Mhz clock connected to SAR */
        MAD_2_SAR_CSR0_REG &= (uint8)~MAD_2_SAR_RESET_SOFT_ACTIVE;
    #else
        CyDelayUs(10u); /* The block is ready to use 10 us after the enable signal is set high. */
    #endif /* End CY_PSOC5A */

    #if(MAD_2_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(MAD_2_INTC_NUMBER);
    #endif   /* End MAD_2_IRQ_REMOVE */        

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MAD_2_Stop
********************************************************************************
*
* Summary:
*  Stops convertion and reduce the power to the minimum.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MAD_2_Stop(void)
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Stop all conversions */
    MAD_2_SAR_CSR0_REG &= (uint8)~MAD_2_SAR_SOF_START_CONV;

    #if(CY_PSOC5A)
        /* Leave the SAR block powered and reduce the power to the minimum */
        MAD_2_SAR_CSR0_REG |= MAD_2_ICONT_LV_3;
         /* Disconnect Bypass Cap */
        MAD_2_SAR_CSR6_REG &= (uint8)~MAD_2_INT_BYPASS_EXT_VREF;
        /* Disable reference buffer and reduce the reference power to the minimum */
        MAD_2_SAR_CSR3_REG &= (uint8)~MAD_2_SAR_EN_BUF_VREF_EN; /*VCM buffer is absent in PSOC5A*/
        MAD_2_SAR_CSR3_REG |= MAD_2_SAR_PWR_CTRL_VREF_DIV_BY4;
    #else
        /* Disable the SAR ADC block in Active Power Mode */
        MAD_2_PWRMGR_SAR_REG &= (uint8)~MAD_2_ACT_PWR_SAR_EN;
        /* Disable the SAR ADC in Standby Power Mode */
        MAD_2_STBY_PWRMGR_SAR_REG &= (uint8)~MAD_2_STBY_PWR_SAR_EN;
    #endif /* End CY_PSOC5A */

    /* This is only valid if there is an internal clock */
    #if(MAD_2_DEFAULT_INTERNAL_CLK)
        MAD_2_PWRMGR_CLK_REG &= (uint8)~MAD_2_ACT_PWR_CLK_EN;
        MAD_2_STBY_PWRMGR_CLK_REG &= (uint8)~MAD_2_STBY_PWR_CLK_EN;
    #endif /* End MAD_2_DEFAULT_INTERNAL_CLK */

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: MAD_2_SetPower
********************************************************************************
*
* Summary:
*  Sets the Power mode.
*
* Parameters:
*  power:  Power setting for ADC
*  0 ->    Normal
*  1 ->    Half power
*  2 ->    1/3rd power
*  3 ->    Quarter power.
*
* Return:
*  None.
*
*******************************************************************************/
void MAD_2_SetPower(uint8 power)
{
    uint8 tmpReg;

    /* mask off invalid power settings */
    power &= MAD_2_SAR_API_POWER_MASK;

    /* Set Power parameter  */
    tmpReg = MAD_2_SAR_CSR0_REG & (uint8)~MAD_2_SAR_POWER_MASK;
    tmpReg |= (uint8)(power << MAD_2_SAR_POWER_SHIFT);
    MAD_2_SAR_CSR0_REG = tmpReg;
}


/*******************************************************************************
* Function Name: MAD_2_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*  This function does not affect the actual conversion with PSoC5 ES1 silicon.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  None.
*
* Side Effects:
*  The ADC resolution cannot be changed during a conversion cycle. The
*  recommended best practice is to stop conversions with
*  ADC_StopConvert(), change the resolution, then restart the
*  conversions with ADC_StartConvert().
*  If you decide not to stop conversions before calling this API, you
*  should use ADC_IsEndConversion() to wait until conversion is complete
*  before changing the resolution.
*  If you call ADC_SetResolution() during a conversion, the resolution will
*  not be changed until the current conversion is complete. Data will not be
*  available in the new resolution for another 6 + "New Resolution(in bits)"
*  clock cycles.
*  You may need add a delay of this number of clock cycles after
*  ADC_SetResolution() is called before data is valid again.
*  Affects ADC_CountsTo_Volts(), ADC_CountsTo_mVolts(), and
*  ADC_CountsTo_uVolts() by calculating the correct conversion between ADC
*  counts and the applied input voltage. Calculation depends on resolution,
*  input range, and voltage reference.
*
*******************************************************************************/
void MAD_2_SetResolution(uint8 resolution)
{
    uint8 tmpReg;

    /* remember resolution for the GetResult APIs */
    #if(CY_PSOC5A)
        MAD_2_resolution = resolution;
    #endif /* End CY_PSOC5A */

    /* Set SAR ADC resolution and sample width: 18 conversion cycles at 12bits + 1 gap */
    switch (resolution)
    {
        case (uint8)MAD_2__BITS_12:
            tmpReg = MAD_2_SAR_RESOLUTION_12BIT | MAD_2_SAR_SAMPLE_WIDTH;
            break;
        case (uint8)MAD_2__BITS_10:
            /* Use 12bits for PSoC5 production silicon and shift the
            *  results for lower resolution in GetResult16() API
            */
            #if(CY_PSOC5A)
                tmpReg = MAD_2_SAR_RESOLUTION_12BIT | MAD_2_SAR_SAMPLE_WIDTH;
            #else
                tmpReg = MAD_2_SAR_RESOLUTION_10BIT | MAD_2_SAR_SAMPLE_WIDTH;
            #endif /* End CY_PSOC5A */
            break;
        case (uint8)MAD_2__BITS_8:
            #if(CY_PSOC5A)
                tmpReg = MAD_2_SAR_RESOLUTION_12BIT | MAD_2_SAR_SAMPLE_WIDTH;
            #else
                tmpReg = MAD_2_SAR_RESOLUTION_8BIT | MAD_2_SAR_SAMPLE_WIDTH;
            #endif /* End CY_PSOC5A */
            break;
        default:
            tmpReg = MAD_2_SAR_RESOLUTION_12BIT | MAD_2_SAR_SAMPLE_WIDTH;
            /* Halt CPU in debug mode if resolution is out of valid range */
            CYASSERT(0u != 0u);
            break;
    }
    MAD_2_SAR_CSR2_REG = tmpReg;

     /* Calculate gain for convert counts to volts */
    MAD_2_CalcGain(resolution);
}


#if(MAD_2_DEFAULT_CONV_MODE != MAD_2__HARDWARE_TRIGGER)


    /*******************************************************************************
    * Function Name: MAD_2_StartConvert
    ********************************************************************************
    *
    * Summary:
    *  Starts ADC conversion using the given mode. The API is available in the 
    *  free running and the software trigger mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Forces the ADC to initiate a conversion. In Free Running mode, the ADC will
    *  run continuously. In a software trigger mode the function also acts as a 
    *  software version of the SOC. Here every conversion has to be triggered by 
    *  the routine. This writes into the SOC bit in SAR_CTRL reg.
    *
    * Side Effects:
    *  In a software trigger mode the function switches source for SOF from the 
    *  external pin to the internal SOF generation. Application should not call 
    *  StartConvert if external source used for SOF.
    *******************************************************************************/
    void MAD_2_StartConvert(void)
    {
        #if(MAD_2_DEFAULT_CONV_MODE != MAD_2__FREE_RUNNING)  /* If software triggered mode */
            MAD_2_SAR_CSR0_REG &= (uint8)~MAD_2_SAR_MX_SOF_UDB;   /* source: SOF bit */
        #endif /* End MAD_2_DEFAULT_CONV_MODE */

        /* Start the conversion */
        MAD_2_SAR_CSR0_REG |= MAD_2_SAR_SOF_START_CONV;
    }


    /*******************************************************************************
    * Function Name: MAD_2_StopConvert
    ********************************************************************************
    *
    * Summary:
    *  Stops ADC conversion using the given mode. The API is available in the 
    *  free running and the software trigger mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Stops ADC conversion in Free Running mode.
    *  This writes into the SOC bit in SAR_CTRL reg.
    *
    * Side Effects:
    *  In a software trigger mode the function set a software version of the SOC 
    *  to low level and switch SOF source to hardware SOF input.
    *
    *******************************************************************************/
    void MAD_2_StopConvert(void)
    {
        /* Stop all conversions */
        MAD_2_SAR_CSR0_REG &= (uint8)~MAD_2_SAR_SOF_START_CONV;

        #if(MAD_2_DEFAULT_CONV_MODE != MAD_2__FREE_RUNNING)  /* If software triggered mode */
            /* Return source to UDB for hardware SOF signal */
            MAD_2_SAR_CSR0_REG |= MAD_2_SAR_MX_SOF_UDB;    /* source: UDB */
        #endif /* End MAD_2_DEFAULT_CONV_MODE */

    }

#endif /* End MAD_2_DEFAULT_CONV_MODE != MAD_2__HARDWARE_TRIGGER */


/*******************************************************************************
* Function Name: MAD_2_IsEndConversion
********************************************************************************
*
* Summary:
*  Queries the ADC to see if conversion is complete
*
* Parameters:
*  retMode:  Wait mode,
*   0 if return with answer imediately.
*   1 if wait until conversion is complete, then return.
*
* Return:
*  (uint8)  0 =>  Conversion not complete.
*           1 =>  Conversion complete.
*
*******************************************************************************/
uint8 MAD_2_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
        status = MAD_2_SAR_CSR1_REG & MAD_2_SAR_EOF_1;
    } while ((status != MAD_2_SAR_EOF_1) && (retMode == MAD_2_WAIT_FOR_RESULT));
    /* If convertion complete, wait until EOF bit released */
    if(status == MAD_2_SAR_EOF_1)
    {
        /* wait one ADC clock to let the EOC status bit release */
        CyDelayUs(1u);
        /* Do the unconditional read operation of the CSR1 register to make sure the EOC bit has been cleared */
        CY_GET_REG8(MAD_2_SAR_CSR1_PTR);
    }

    return(status);
}


/*******************************************************************************
* Function Name: MAD_2_GetResult8
********************************************************************************
*
* Summary:
*  Returns an 8-bit result or the LSB of the last conversion.
*  MAD_2_IsEndConversion() should be called to verify that the data
*   sample is ready
*
* Parameters:
*  None.
*
* Return:
*  ADC result.
*
* Global Variables:
*  MAD_2_shift - used to convert the ADC counts to the 2's
*  compliment form.
*  MAD_2_resolution - used to shift the results for lower
*   resolution.
*
*******************************************************************************/
int8 MAD_2_GetResult8( void )
{

    #if(CY_PSOC5A)

        uint16 res;

        res = CY_GET_REG16(MAD_2_SAR_WRK_PTR);

        /* Use 12bits for PSoC5 production silicon and shift the results for lower resolution in this API */
        switch (MAD_2_resolution)
        {
            case (uint8)MAD_2__BITS_10:
                res >>= 2u;
                break;
            case (uint8)MAD_2__BITS_8:
                res >>= 4u;
                break;
            default: /* Do not shift for 12 bits */
                break;
        }
        return( (int8)((int16)res - MAD_2_shift) );
    #else
        return( (int8)MAD_2_SAR_WRK0_REG - (int8)MAD_2_shift);
    #endif /* End CY_PSOC5A */

}


/*******************************************************************************
* Function Name: MAD_2_GetResult16
********************************************************************************
*
* Summary:
*  Gets the data available in the SAR DATA registers.
*  MAD_2_IsEndConversion() should be called to verify that the data
*   sample is ready
*
* Parameters:
*  None.
*
* Return:
*  ADC result. WORD value which has the converted 12bits. In the differential
*  input mode the SAR ADC outputs digitally converted data in binary offset
*  scheme, this function converts the data into 2's compliment form.
*
* Global Variables:
*  MAD_2_shift - used to convert the ADC counts to the 2's
*  compliment form.
*  MAD_2_resolution - used to shift the results for lower
*   resolution.
*
*******************************************************************************/
int16 MAD_2_GetResult16( void )
{
    uint16 res;

    res = CY_GET_REG16(MAD_2_SAR_WRK_PTR);

    #if(CY_PSOC5A)
        /* Use 12bits for PSoC5 production silicon and shift the results for lower resolution in this API */
        switch (MAD_2_resolution)
        {
            case (uint8)MAD_2__BITS_10:
                res >>= 2u;
                break;
            case (uint8)MAD_2__BITS_8:
                res >>= 4u;
                break;
            default: /* Do not shift for 12 bits */
                break;
        }
    #endif /* End CY_PSOC5A */

    return( (int16)res - MAD_2_shift );
}


/*******************************************************************************
* Function Name: MAD_2_SetOffset
********************************************************************************
*
* Summary:
*  This function sets the offset for voltage readings.
*
* Parameters:
*  int16: Offset in counts
*
* Return:
*  None.
*
* Global Variables:
*  The MAD_2_offset variable modified. This variable is used for
*  offset calibration purpose.
*  Affects the MAD_2_CountsTo_Volts,
*  MAD_2_CountsTo_mVolts, MAD_2_CountsTo_uVolts functions
*  by subtracting the given offset.
*
*******************************************************************************/
void MAD_2_SetOffset(int16 offset)
{
    MAD_2_offset = offset;
}


/*******************************************************************************
* Function Name: MAD_2_CalcGain
********************************************************************************
*
* Summary:
*  This function calculates the ADC gain in counts per volt.
*
* Parameters:
*  uint8: resolution
*
* Return:
*  None.
*
* Global Variables:
*  MAD_2_shift variable initialized. This variable is used to
*  convert the ADC counts to the 2's compliment form.
*  MAD_2_countsPerVolt variable initialized. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
static void MAD_2_CalcGain( uint8 resolution )
{
    int32 counts;
    #if(!((MAD_2_DEFAULT_RANGE == MAD_2__VSS_TO_VREF) || \
         (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDDA) || \
         (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDAC)) )
        uint16 diff_zero;
    #endif /* End MAD_2_DEFAULT_RANGE */

    switch (resolution)
    {
        case (uint8)MAD_2__BITS_12:
            counts = (int32)MAD_2_SAR_WRK_MAX;
            #if(!((MAD_2_DEFAULT_RANGE == MAD_2__VSS_TO_VREF) || \
                 (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDDA) || \
                 (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDAC)) )
                diff_zero = MAD_2_SAR_DIFF_SHIFT;
            #endif /* End MAD_2_DEFAULT_RANGE */
            break;
        case (uint8)MAD_2__BITS_10:
            counts = (int32)(MAD_2_SAR_WRK_MAX >> 2u);
            #if(!((MAD_2_DEFAULT_RANGE == MAD_2__VSS_TO_VREF) || \
                 (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDDA) || \
                 (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDAC)) )
                diff_zero = MAD_2_SAR_DIFF_SHIFT >> 2u;
            #endif /* End MAD_2_DEFAULT_RANGE */
            break;
        case (uint8)MAD_2__BITS_8:
            counts = (int32)(MAD_2_SAR_WRK_MAX >> 4u);
            #if(!((MAD_2_DEFAULT_RANGE == MAD_2__VSS_TO_VREF) || \
                 (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDDA) || \
                 (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDAC)) )
                diff_zero = MAD_2_SAR_DIFF_SHIFT >> 4u;
            #endif /* End MAD_2_DEFAULT_RANGE */
            break;
        default: /* Halt CPU in debug mode if resolution is out of valid range */
            counts = 0;
            #if(!((MAD_2_DEFAULT_RANGE == MAD_2__VSS_TO_VREF) || \
                 (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDDA) || \
                 (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDAC)) )
                diff_zero = 0u;
            #endif /* End MAD_2_DEFAULT_RANGE */
            CYASSERT(0u != 0u);
            break;
    }
    counts *= 1000; /* To avoid float point arithmetic*/
    MAD_2_countsPerVolt = (int16)(counts / MAD_2_DEFAULT_REF_VOLTAGE_MV / 2);

    #if( (MAD_2_DEFAULT_RANGE == MAD_2__VSS_TO_VREF) || \
         (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDDA) || \
         (MAD_2_DEFAULT_RANGE == MAD_2__VSSA_TO_VDAC) )
        MAD_2_shift = 0;
    #else
        MAD_2_shift = diff_zero;
    #endif /* End MAD_2_DEFAULT_RANGE */
}


/*******************************************************************************
* Function Name: MAD_2_SetGain
********************************************************************************
*
* Summary:
*  This function sets the ADC gain in counts per volt.
*
* Parameters:
*  int16  adcGain  counts per volt
*
* Return:
*  None.
*
* Global Variables:
*  MAD_2_countsPerVolt variable modified. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
void MAD_2_SetGain(int16 adcGain)
{
    MAD_2_countsPerVolt = adcGain;
}


/*******************************************************************************
* Function Name: MAD_2_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to mVolts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  int16  Result in mVolts
*
* Global Variables:
*  MAD_2_offset variable used.
*  MAD_2_countsPerVolt variable used.
*
*******************************************************************************/
int16 MAD_2_CountsTo_mVolts(int16 adcCounts)
{

    int16 mVolts;

    /* Subtract ADC offset */
    adcCounts -= MAD_2_offset;

    mVolts = (int16)(( (int32)adcCounts * 1000 ) / MAD_2_countsPerVolt) ;

    return( mVolts );
}


/*******************************************************************************
* Function Name: MAD_2_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to micro Volts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  int32  Result in micro Volts
*
* Global Variables:
*  MAD_2_offset variable used.
*  MAD_2_countsPerVolt variable used.
*
*******************************************************************************/
int32 MAD_2_CountsTo_uVolts(int16 adcCounts)
{

    int32 uVolts;

    /* Subtract ADC offset */
    adcCounts -= MAD_2_offset;
    /* To convert adcCounts to microVolts it is required to be multiplied
    *  on 1 million. It is multiplied on 500000 and later on 2 to
    *  to avoid 32bit arithmetic overflows.
    */
    uVolts = (( (int32)adcCounts * 500000 ) / MAD_2_countsPerVolt) * 2;

    return( uVolts );
}


/*******************************************************************************
* Function Name: MAD_2_CountsTo_Volts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to Volts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  float  Result in mVolts
*
* Global Variables:
*  MAD_2_offset variable used.
*  MAD_2_countsPerVolt variable used.
*
*******************************************************************************/
float32 MAD_2_CountsTo_Volts(int16 adcCounts)
{
    float32 volts;

    /* Subtract ADC offset */
    adcCounts -= MAD_2_offset;

    volts = (float32)adcCounts / (float32)MAD_2_countsPerVolt;

    return( volts );
}


/* [] END OF FILE */
