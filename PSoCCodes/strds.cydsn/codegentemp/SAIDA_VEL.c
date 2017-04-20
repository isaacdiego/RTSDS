/*******************************************************************************
* File Name: SAIDA_VEL.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "SAIDA_VEL.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SAIDA_VEL__PORT == 15 && ((SAIDA_VEL__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SAIDA_VEL_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void SAIDA_VEL_Write(uint8 value) 
{
    uint8 staticBits = (SAIDA_VEL_DR & (uint8)(~SAIDA_VEL_MASK));
    SAIDA_VEL_DR = staticBits | ((uint8)(value << SAIDA_VEL_SHIFT) & SAIDA_VEL_MASK);
}


/*******************************************************************************
* Function Name: SAIDA_VEL_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void SAIDA_VEL_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SAIDA_VEL_0, mode);
}


/*******************************************************************************
* Function Name: SAIDA_VEL_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro SAIDA_VEL_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SAIDA_VEL_Read(void) 
{
    return (SAIDA_VEL_PS & SAIDA_VEL_MASK) >> SAIDA_VEL_SHIFT;
}


/*******************************************************************************
* Function Name: SAIDA_VEL_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 SAIDA_VEL_ReadDataReg(void) 
{
    return (SAIDA_VEL_DR & SAIDA_VEL_MASK) >> SAIDA_VEL_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SAIDA_VEL_INTSTAT) 

    /*******************************************************************************
    * Function Name: SAIDA_VEL_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 SAIDA_VEL_ClearInterrupt(void) 
    {
        return (SAIDA_VEL_INTSTAT & SAIDA_VEL_MASK) >> SAIDA_VEL_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
