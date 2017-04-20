/*******************************************************************************
* File Name: MSG_1_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "MSG_1.h"

static MSG_1_backupStruct MSG_1_backup;


/*******************************************************************************
* Function Name: MSG_1_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void MSG_1_SaveConfig(void) 
{
    if (!((MSG_1_CR1 & MSG_1_SRC_MASK) == MSG_1_SRC_UDB))
    {
        MSG_1_backup.data_value = MSG_1_Data;
    }
}


/*******************************************************************************
* Function Name: MSG_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void MSG_1_RestoreConfig(void) 
{
    if (!((MSG_1_CR1 & MSG_1_SRC_MASK) == MSG_1_SRC_UDB))
    {
        if((MSG_1_Strobe & MSG_1_STRB_MASK) == MSG_1_STRB_EN)
        {
            MSG_1_Strobe &= (uint8)(~MSG_1_STRB_MASK);
            MSG_1_Data = MSG_1_backup.data_value;
            MSG_1_Strobe |= MSG_1_STRB_EN;
        }
        else
        {
            MSG_1_Data = MSG_1_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: MSG_1_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  MSG_1_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void MSG_1_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(MSG_1_ACT_PWR_EN == (MSG_1_PWRMGR & MSG_1_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        MSG_1_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        MSG_1_backup.enableState = 0u;
    }
    
    MSG_1_Stop();
    MSG_1_SaveConfig();
}


/*******************************************************************************
* Function Name: MSG_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  MSG_1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MSG_1_Wakeup(void) 
{
    MSG_1_RestoreConfig();
    
    if(MSG_1_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        MSG_1_Enable();

        /* Restore the data register */
        MSG_1_SetValue(MSG_1_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
