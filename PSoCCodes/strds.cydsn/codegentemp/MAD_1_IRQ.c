/*******************************************************************************
* File Name: MAD_1_IRQ.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <MAD_1_IRQ.H>

#if !defined(MAD_1_IRQ__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START MAD_1_IRQ_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: MAD_1_IRQ_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void MAD_1_IRQ_Start(void)
{
    /* For all we know the interrupt is active. */
    MAD_1_IRQ_Disable();

    /* Set the ISR to point to the MAD_1_IRQ Interrupt. */
    MAD_1_IRQ_SetVector(&MAD_1_IRQ_Interrupt);

    /* Set the priority. */
    MAD_1_IRQ_SetPriority((uint8)MAD_1_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    MAD_1_IRQ_Enable();
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void MAD_1_IRQ_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    MAD_1_IRQ_Disable();

    /* Set the ISR to point to the MAD_1_IRQ Interrupt. */
    MAD_1_IRQ_SetVector(address);

    /* Set the priority. */
    MAD_1_IRQ_SetPriority((uint8)MAD_1_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    MAD_1_IRQ_Enable();
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void MAD_1_IRQ_Stop(void)
{
    /* Disable this interrupt. */
    MAD_1_IRQ_Disable();

    /* Set the ISR to point to the passive one. */
    MAD_1_IRQ_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for MAD_1_IRQ.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(MAD_1_IRQ_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START MAD_1_IRQ_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling MAD_1_IRQ_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use MAD_1_IRQ_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void MAD_1_IRQ_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)MAD_1_IRQ__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress MAD_1_IRQ_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)MAD_1_IRQ__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling MAD_1_IRQ_Start
*   or MAD_1_IRQ_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   MAD_1_IRQ_Start or MAD_1_IRQ_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void MAD_1_IRQ_SetPriority(uint8 priority)
{
    *MAD_1_IRQ_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 MAD_1_IRQ_GetPriority(void)
{
    uint8 priority;


    priority = *MAD_1_IRQ_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void MAD_1_IRQ_Enable(void)
{
    /* Enable the general interrupt. */
    *MAD_1_IRQ_INTC_SET_EN = MAD_1_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 MAD_1_IRQ_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*MAD_1_IRQ_INTC_SET_EN & (uint32)MAD_1_IRQ__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void MAD_1_IRQ_Disable(void)
{
    /* Disable the general interrupt. */
    *MAD_1_IRQ_INTC_CLR_EN = MAD_1_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void MAD_1_IRQ_SetPending(void)
{
    *MAD_1_IRQ_INTC_SET_PD = MAD_1_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: MAD_1_IRQ_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void MAD_1_IRQ_ClearPending(void)
{
    *MAD_1_IRQ_INTC_CLR_PD = MAD_1_IRQ__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
