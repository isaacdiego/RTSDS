/*******************************************************************************
* File Name: PINO_PROCESSAMENTO.c  
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
#include "PINO_PROCESSAMENTO.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 PINO_PROCESSAMENTO__PORT == 15 && ((PINO_PROCESSAMENTO__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: PINO_PROCESSAMENTO_Write
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
void PINO_PROCESSAMENTO_Write(uint8 value) 
{
    uint8 staticBits = (PINO_PROCESSAMENTO_DR & (uint8)(~PINO_PROCESSAMENTO_MASK));
    PINO_PROCESSAMENTO_DR = staticBits | ((uint8)(value << PINO_PROCESSAMENTO_SHIFT) & PINO_PROCESSAMENTO_MASK);
}


/*******************************************************************************
* Function Name: PINO_PROCESSAMENTO_SetDriveMode
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
void PINO_PROCESSAMENTO_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PINO_PROCESSAMENTO_0, mode);
}


/*******************************************************************************
* Function Name: PINO_PROCESSAMENTO_Read
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
*  Macro PINO_PROCESSAMENTO_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PINO_PROCESSAMENTO_Read(void) 
{
    return (PINO_PROCESSAMENTO_PS & PINO_PROCESSAMENTO_MASK) >> PINO_PROCESSAMENTO_SHIFT;
}


/*******************************************************************************
* Function Name: PINO_PROCESSAMENTO_ReadDataReg
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
uint8 PINO_PROCESSAMENTO_ReadDataReg(void) 
{
    return (PINO_PROCESSAMENTO_DR & PINO_PROCESSAMENTO_MASK) >> PINO_PROCESSAMENTO_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PINO_PROCESSAMENTO_INTSTAT) 

    /*******************************************************************************
    * Function Name: PINO_PROCESSAMENTO_ClearInterrupt
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
    uint8 PINO_PROCESSAMENTO_ClearInterrupt(void) 
    {
        return (PINO_PROCESSAMENTO_INTSTAT & PINO_PROCESSAMENTO_MASK) >> PINO_PROCESSAMENTO_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
