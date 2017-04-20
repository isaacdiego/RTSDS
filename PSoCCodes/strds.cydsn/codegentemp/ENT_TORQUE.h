/*******************************************************************************
* File Name: ENT_TORQUE.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ENT_TORQUE_H) /* Pins ENT_TORQUE_H */
#define CY_PINS_ENT_TORQUE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ENT_TORQUE_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ENT_TORQUE__PORT == 15 && ((ENT_TORQUE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    ENT_TORQUE_Write(uint8 value) ;
void    ENT_TORQUE_SetDriveMode(uint8 mode) ;
uint8   ENT_TORQUE_ReadDataReg(void) ;
uint8   ENT_TORQUE_Read(void) ;
uint8   ENT_TORQUE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ENT_TORQUE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define ENT_TORQUE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define ENT_TORQUE_DM_RES_UP          PIN_DM_RES_UP
#define ENT_TORQUE_DM_RES_DWN         PIN_DM_RES_DWN
#define ENT_TORQUE_DM_OD_LO           PIN_DM_OD_LO
#define ENT_TORQUE_DM_OD_HI           PIN_DM_OD_HI
#define ENT_TORQUE_DM_STRONG          PIN_DM_STRONG
#define ENT_TORQUE_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define ENT_TORQUE_MASK               ENT_TORQUE__MASK
#define ENT_TORQUE_SHIFT              ENT_TORQUE__SHIFT
#define ENT_TORQUE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ENT_TORQUE_PS                     (* (reg8 *) ENT_TORQUE__PS)
/* Data Register */
#define ENT_TORQUE_DR                     (* (reg8 *) ENT_TORQUE__DR)
/* Port Number */
#define ENT_TORQUE_PRT_NUM                (* (reg8 *) ENT_TORQUE__PRT) 
/* Connect to Analog Globals */                                                  
#define ENT_TORQUE_AG                     (* (reg8 *) ENT_TORQUE__AG)                       
/* Analog MUX bux enable */
#define ENT_TORQUE_AMUX                   (* (reg8 *) ENT_TORQUE__AMUX) 
/* Bidirectional Enable */                                                        
#define ENT_TORQUE_BIE                    (* (reg8 *) ENT_TORQUE__BIE)
/* Bit-mask for Aliased Register Access */
#define ENT_TORQUE_BIT_MASK               (* (reg8 *) ENT_TORQUE__BIT_MASK)
/* Bypass Enable */
#define ENT_TORQUE_BYP                    (* (reg8 *) ENT_TORQUE__BYP)
/* Port wide control signals */                                                   
#define ENT_TORQUE_CTL                    (* (reg8 *) ENT_TORQUE__CTL)
/* Drive Modes */
#define ENT_TORQUE_DM0                    (* (reg8 *) ENT_TORQUE__DM0) 
#define ENT_TORQUE_DM1                    (* (reg8 *) ENT_TORQUE__DM1)
#define ENT_TORQUE_DM2                    (* (reg8 *) ENT_TORQUE__DM2) 
/* Input Buffer Disable Override */
#define ENT_TORQUE_INP_DIS                (* (reg8 *) ENT_TORQUE__INP_DIS)
/* LCD Common or Segment Drive */
#define ENT_TORQUE_LCD_COM_SEG            (* (reg8 *) ENT_TORQUE__LCD_COM_SEG)
/* Enable Segment LCD */
#define ENT_TORQUE_LCD_EN                 (* (reg8 *) ENT_TORQUE__LCD_EN)
/* Slew Rate Control */
#define ENT_TORQUE_SLW                    (* (reg8 *) ENT_TORQUE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ENT_TORQUE_PRTDSI__CAPS_SEL       (* (reg8 *) ENT_TORQUE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ENT_TORQUE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ENT_TORQUE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ENT_TORQUE_PRTDSI__OE_SEL0        (* (reg8 *) ENT_TORQUE__PRTDSI__OE_SEL0) 
#define ENT_TORQUE_PRTDSI__OE_SEL1        (* (reg8 *) ENT_TORQUE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ENT_TORQUE_PRTDSI__OUT_SEL0       (* (reg8 *) ENT_TORQUE__PRTDSI__OUT_SEL0) 
#define ENT_TORQUE_PRTDSI__OUT_SEL1       (* (reg8 *) ENT_TORQUE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ENT_TORQUE_PRTDSI__SYNC_OUT       (* (reg8 *) ENT_TORQUE__PRTDSI__SYNC_OUT) 


#if defined(ENT_TORQUE__INTSTAT)  /* Interrupt Registers */

    #define ENT_TORQUE_INTSTAT                (* (reg8 *) ENT_TORQUE__INTSTAT)
    #define ENT_TORQUE_SNAP                   (* (reg8 *) ENT_TORQUE__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ENT_TORQUE_H */


/* [] END OF FILE */
