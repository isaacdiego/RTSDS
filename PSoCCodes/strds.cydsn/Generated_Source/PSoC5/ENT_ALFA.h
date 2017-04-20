/*******************************************************************************
* File Name: ENT_ALFA.h  
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

#if !defined(CY_PINS_ENT_ALFA_H) /* Pins ENT_ALFA_H */
#define CY_PINS_ENT_ALFA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ENT_ALFA_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ENT_ALFA__PORT == 15 && ((ENT_ALFA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    ENT_ALFA_Write(uint8 value) ;
void    ENT_ALFA_SetDriveMode(uint8 mode) ;
uint8   ENT_ALFA_ReadDataReg(void) ;
uint8   ENT_ALFA_Read(void) ;
uint8   ENT_ALFA_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ENT_ALFA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define ENT_ALFA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define ENT_ALFA_DM_RES_UP          PIN_DM_RES_UP
#define ENT_ALFA_DM_RES_DWN         PIN_DM_RES_DWN
#define ENT_ALFA_DM_OD_LO           PIN_DM_OD_LO
#define ENT_ALFA_DM_OD_HI           PIN_DM_OD_HI
#define ENT_ALFA_DM_STRONG          PIN_DM_STRONG
#define ENT_ALFA_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define ENT_ALFA_MASK               ENT_ALFA__MASK
#define ENT_ALFA_SHIFT              ENT_ALFA__SHIFT
#define ENT_ALFA_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ENT_ALFA_PS                     (* (reg8 *) ENT_ALFA__PS)
/* Data Register */
#define ENT_ALFA_DR                     (* (reg8 *) ENT_ALFA__DR)
/* Port Number */
#define ENT_ALFA_PRT_NUM                (* (reg8 *) ENT_ALFA__PRT) 
/* Connect to Analog Globals */                                                  
#define ENT_ALFA_AG                     (* (reg8 *) ENT_ALFA__AG)                       
/* Analog MUX bux enable */
#define ENT_ALFA_AMUX                   (* (reg8 *) ENT_ALFA__AMUX) 
/* Bidirectional Enable */                                                        
#define ENT_ALFA_BIE                    (* (reg8 *) ENT_ALFA__BIE)
/* Bit-mask for Aliased Register Access */
#define ENT_ALFA_BIT_MASK               (* (reg8 *) ENT_ALFA__BIT_MASK)
/* Bypass Enable */
#define ENT_ALFA_BYP                    (* (reg8 *) ENT_ALFA__BYP)
/* Port wide control signals */                                                   
#define ENT_ALFA_CTL                    (* (reg8 *) ENT_ALFA__CTL)
/* Drive Modes */
#define ENT_ALFA_DM0                    (* (reg8 *) ENT_ALFA__DM0) 
#define ENT_ALFA_DM1                    (* (reg8 *) ENT_ALFA__DM1)
#define ENT_ALFA_DM2                    (* (reg8 *) ENT_ALFA__DM2) 
/* Input Buffer Disable Override */
#define ENT_ALFA_INP_DIS                (* (reg8 *) ENT_ALFA__INP_DIS)
/* LCD Common or Segment Drive */
#define ENT_ALFA_LCD_COM_SEG            (* (reg8 *) ENT_ALFA__LCD_COM_SEG)
/* Enable Segment LCD */
#define ENT_ALFA_LCD_EN                 (* (reg8 *) ENT_ALFA__LCD_EN)
/* Slew Rate Control */
#define ENT_ALFA_SLW                    (* (reg8 *) ENT_ALFA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ENT_ALFA_PRTDSI__CAPS_SEL       (* (reg8 *) ENT_ALFA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ENT_ALFA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ENT_ALFA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ENT_ALFA_PRTDSI__OE_SEL0        (* (reg8 *) ENT_ALFA__PRTDSI__OE_SEL0) 
#define ENT_ALFA_PRTDSI__OE_SEL1        (* (reg8 *) ENT_ALFA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ENT_ALFA_PRTDSI__OUT_SEL0       (* (reg8 *) ENT_ALFA__PRTDSI__OUT_SEL0) 
#define ENT_ALFA_PRTDSI__OUT_SEL1       (* (reg8 *) ENT_ALFA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ENT_ALFA_PRTDSI__SYNC_OUT       (* (reg8 *) ENT_ALFA__PRTDSI__SYNC_OUT) 


#if defined(ENT_ALFA__INTSTAT)  /* Interrupt Registers */

    #define ENT_ALFA_INTSTAT                (* (reg8 *) ENT_ALFA__INTSTAT)
    #define ENT_ALFA_SNAP                   (* (reg8 *) ENT_ALFA__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ENT_ALFA_H */


/* [] END OF FILE */
