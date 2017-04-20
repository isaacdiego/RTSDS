/*******************************************************************************
* File Name: MAD_2_PM.c
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

#include "MAD_2.h"


/***************************************
* Local data allocation
***************************************/

static MAD_2_BACKUP_STRUCT  MAD_2_backup =
{
    MAD_2_DISABLED
};


/*******************************************************************************
* Function Name: MAD_2_SaveConfig
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
void MAD_2_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: MAD_2_RestoreConfig
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
void MAD_2_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: MAD_2_Sleep
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
*  MAD_2_backup - modified.
*
*******************************************************************************/
void MAD_2_Sleep(void)
{
    if((MAD_2_PWRMGR_SAR_REG  & MAD_2_ACT_PWR_SAR_EN) != 0u)
    {
        if((MAD_2_SAR_CSR0_REG & MAD_2_SAR_SOF_START_CONV) != 0u)
        {
            MAD_2_backup.enableState = MAD_2_ENABLED | MAD_2_STARTED;
        }
        else
        {
            MAD_2_backup.enableState = MAD_2_ENABLED;
        }
        MAD_2_Stop();
    }
    else
    {
        MAD_2_backup.enableState = MAD_2_DISABLED;
    }
    /*MAD_2_SaveConfig();*/
}


/*******************************************************************************
* Function Name: MAD_2_Wakeup
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
*  MAD_2_backup - used.
*
*******************************************************************************/
void MAD_2_Wakeup(void)
{
    /*MAD_2_RestoreConfig();*/
    if(MAD_2_backup.enableState != MAD_2_DISABLED)
    {
        MAD_2_Enable();
        #if(MAD_2_DEFAULT_CONV_MODE != MAD_2__HARDWARE_TRIGGER)
            if((MAD_2_backup.enableState & MAD_2_STARTED) != 0u)
            {
                MAD_2_StartConvert();
            }
        #endif /* End MAD_2_DEFAULT_CONV_MODE != MAD_2__HARDWARE_TRIGGER */
        
    }
}


/* [] END OF FILE */
