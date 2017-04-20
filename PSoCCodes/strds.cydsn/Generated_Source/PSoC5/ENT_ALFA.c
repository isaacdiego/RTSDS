/*******************************************************************************
* File Name: ENT_ALFA.c  
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
#include "ENT_ALFA.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 ENT_ALFA__PORT == 15 && ((ENT_ALFA__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: ENT_ALFA_Write
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
void ENT_ALFA_Write(uint8 value) 
{
    uint8 staticBits = (ENT_ALFA_DR & (uint8)(~ENT_ALFA_MASK));
    ENT_ALFA_DR = staticBits | ((uint8)(value << ENT_ALFA_SHIFT) & ENT_ALFA_MASK);
}


/*******************************************************************************
* Function Name: ENT_ALFA_SetDriveMode
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
void ENT_ALFA_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ENT_ALFA_0, mode);
}


/*******************************************************************************
* Function Name: ENT_ALFA_Read
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
*  Macro ENT_ALFA_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ENT_ALFA_Read(void) 
{
    return (ENT_ALFA_PS & ENT_ALFA_MASK) >> ENT_ALFA_SHIFT;
}


/*******************************************************************************
* Function Name: ENT_ALFA_ReadDataReg
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
uint8 ENT_ALFA_ReadDataReg(void) 
{
    return (ENT_ALFA_DR & ENT_ALFA_MASK) >> ENT_ALFA_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ENT_ALFA_INTSTAT) 

    /*******************************************************************************
    * Function Name: ENT_ALFA_ClearInterrupt
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
    uint8 ENT_ALFA_ClearInterrupt(void) 
    {
        return (ENT_ALFA_INTSTAT & ENT_ALFA_MASK) >> ENT_ALFA_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
