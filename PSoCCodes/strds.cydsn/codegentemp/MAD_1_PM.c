/*******************************************************************************
* File Name: MAD_1_PM.c
* Version 2.0
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MAD_1.h"


/***************************************
* Local data allocation
***************************************/

static MAD_1_BACKUP_STRUCT  MAD_1_backup =
{
    MAD_1_DISABLED
};


/*******************************************************************************
* Function Name: MAD_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MAD_1_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: MAD_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MAD_1_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: MAD_1_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MAD_1_backup - modified.
*
*******************************************************************************/
void MAD_1_Sleep(void)
{
    if((MAD_1_PWRMGR_SAR_REG  & MAD_1_ACT_PWR_SAR_EN) != 0u)
    {
        if((MAD_1_SAR_CSR0_REG & MAD_1_SAR_SOF_START_CONV) != 0u)
        {
            MAD_1_backup.enableState = MAD_1_ENABLED | MAD_1_STARTED;
        }
        else
        {
            MAD_1_backup.enableState = MAD_1_ENABLED;
        }
        MAD_1_Stop();
    }
    else
    {
        MAD_1_backup.enableState = MAD_1_DISABLED;
    }
    /*MAD_1_SaveConfig();*/
}


/*******************************************************************************
* Function Name: MAD_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MAD_1_backup - used.
*
*******************************************************************************/
void MAD_1_Wakeup(void)
{
    /*MAD_1_RestoreConfig();*/
    if(MAD_1_backup.enableState != MAD_1_DISABLED)
    {
        MAD_1_Enable();
        #if(MAD_1_DEFAULT_CONV_MODE != MAD_1__HARDWARE_TRIGGER)
            if((MAD_1_backup.enableState & MAD_1_STARTED) != 0u)
            {
                MAD_1_StartConvert();
            }
        #endif /* End MAD_1_DEFAULT_CONV_MODE != MAD_1__HARDWARE_TRIGGER */
        
    }
}


/* [] END OF FILE */
