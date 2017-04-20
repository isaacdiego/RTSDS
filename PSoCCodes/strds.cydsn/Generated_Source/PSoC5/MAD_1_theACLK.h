/*******************************************************************************
* File Name: MAD_1_theACLK.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_MAD_1_theACLK_H)
#define CY_CLOCK_MAD_1_theACLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void MAD_1_theACLK_Start(void) ;
void MAD_1_theACLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void MAD_1_theACLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void MAD_1_theACLK_StandbyPower(uint8 state) ;
void MAD_1_theACLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 MAD_1_theACLK_GetDividerRegister(void) ;
void MAD_1_theACLK_SetModeRegister(uint8 modeBitMask) ;
void MAD_1_theACLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 MAD_1_theACLK_GetModeRegister(void) ;
void MAD_1_theACLK_SetSourceRegister(uint8 clkSource) ;
uint8 MAD_1_theACLK_GetSourceRegister(void) ;
#if defined(MAD_1_theACLK__CFG3)
void MAD_1_theACLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 MAD_1_theACLK_GetPhaseRegister(void) ;
#endif /* defined(MAD_1_theACLK__CFG3) */

#define MAD_1_theACLK_Enable()                       MAD_1_theACLK_Start()
#define MAD_1_theACLK_Disable()                      MAD_1_theACLK_Stop()
#define MAD_1_theACLK_SetDivider(clkDivider)         MAD_1_theACLK_SetDividerRegister(clkDivider, 1)
#define MAD_1_theACLK_SetDividerValue(clkDivider)    MAD_1_theACLK_SetDividerRegister((clkDivider) - 1, 1)
#define MAD_1_theACLK_SetMode(clkMode)               MAD_1_theACLK_SetModeRegister(clkMode)
#define MAD_1_theACLK_SetSource(clkSource)           MAD_1_theACLK_SetSourceRegister(clkSource)
#if defined(MAD_1_theACLK__CFG3)
#define MAD_1_theACLK_SetPhase(clkPhase)             MAD_1_theACLK_SetPhaseRegister(clkPhase)
#define MAD_1_theACLK_SetPhaseValue(clkPhase)        MAD_1_theACLK_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(MAD_1_theACLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define MAD_1_theACLK_CLKEN              (* (reg8 *) MAD_1_theACLK__PM_ACT_CFG)
#define MAD_1_theACLK_CLKEN_PTR          ((reg8 *) MAD_1_theACLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define MAD_1_theACLK_CLKSTBY            (* (reg8 *) MAD_1_theACLK__PM_STBY_CFG)
#define MAD_1_theACLK_CLKSTBY_PTR        ((reg8 *) MAD_1_theACLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define MAD_1_theACLK_DIV_LSB            (* (reg8 *) MAD_1_theACLK__CFG0)
#define MAD_1_theACLK_DIV_LSB_PTR        ((reg8 *) MAD_1_theACLK__CFG0)
#define MAD_1_theACLK_DIV_PTR            ((reg16 *) MAD_1_theACLK__CFG0)

/* Clock MSB divider configuration register. */
#define MAD_1_theACLK_DIV_MSB            (* (reg8 *) MAD_1_theACLK__CFG1)
#define MAD_1_theACLK_DIV_MSB_PTR        ((reg8 *) MAD_1_theACLK__CFG1)

/* Mode and source configuration register */
#define MAD_1_theACLK_MOD_SRC            (* (reg8 *) MAD_1_theACLK__CFG2)
#define MAD_1_theACLK_MOD_SRC_PTR        ((reg8 *) MAD_1_theACLK__CFG2)

#if defined(MAD_1_theACLK__CFG3)
/* Analog clock phase configuration register */
#define MAD_1_theACLK_PHASE              (* (reg8 *) MAD_1_theACLK__CFG3)
#define MAD_1_theACLK_PHASE_PTR          ((reg8 *) MAD_1_theACLK__CFG3)
#endif /* defined(MAD_1_theACLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define MAD_1_theACLK_CLKEN_MASK         MAD_1_theACLK__PM_ACT_MSK
#define MAD_1_theACLK_CLKSTBY_MASK       MAD_1_theACLK__PM_STBY_MSK

/* CFG2 field masks */
#define MAD_1_theACLK_SRC_SEL_MSK        MAD_1_theACLK__CFG2_SRC_SEL_MASK
#define MAD_1_theACLK_MODE_MASK          (~(MAD_1_theACLK_SRC_SEL_MSK))

#if defined(MAD_1_theACLK__CFG3)
/* CFG3 phase mask */
#define MAD_1_theACLK_PHASE_MASK         MAD_1_theACLK__CFG3_PHASE_DLY_MASK
#endif /* defined(MAD_1_theACLK__CFG3) */

#endif /* CY_CLOCK_MAD_1_theACLK_H */


/* [] END OF FILE */
