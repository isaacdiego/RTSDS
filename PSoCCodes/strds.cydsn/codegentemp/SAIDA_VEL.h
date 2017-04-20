/*******************************************************************************
* File Name: SAIDA_VEL.h  
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

#if !defined(CY_PINS_SAIDA_VEL_H) /* Pins SAIDA_VEL_H */
#define CY_PINS_SAIDA_VEL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SAIDA_VEL_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SAIDA_VEL__PORT == 15 && ((SAIDA_VEL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SAIDA_VEL_Write(uint8 value) ;
void    SAIDA_VEL_SetDriveMode(uint8 mode) ;
uint8   SAIDA_VEL_ReadDataReg(void) ;
uint8   SAIDA_VEL_Read(void) ;
uint8   SAIDA_VEL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SAIDA_VEL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SAIDA_VEL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SAIDA_VEL_DM_RES_UP          PIN_DM_RES_UP
#define SAIDA_VEL_DM_RES_DWN         PIN_DM_RES_DWN
#define SAIDA_VEL_DM_OD_LO           PIN_DM_OD_LO
#define SAIDA_VEL_DM_OD_HI           PIN_DM_OD_HI
#define SAIDA_VEL_DM_STRONG          PIN_DM_STRONG
#define SAIDA_VEL_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SAIDA_VEL_MASK               SAIDA_VEL__MASK
#define SAIDA_VEL_SHIFT              SAIDA_VEL__SHIFT
#define SAIDA_VEL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SAIDA_VEL_PS                     (* (reg8 *) SAIDA_VEL__PS)
/* Data Register */
#define SAIDA_VEL_DR                     (* (reg8 *) SAIDA_VEL__DR)
/* Port Number */
#define SAIDA_VEL_PRT_NUM                (* (reg8 *) SAIDA_VEL__PRT) 
/* Connect to Analog Globals */                                                  
#define SAIDA_VEL_AG                     (* (reg8 *) SAIDA_VEL__AG)                       
/* Analog MUX bux enable */
#define SAIDA_VEL_AMUX                   (* (reg8 *) SAIDA_VEL__AMUX) 
/* Bidirectional Enable */                                                        
#define SAIDA_VEL_BIE                    (* (reg8 *) SAIDA_VEL__BIE)
/* Bit-mask for Aliased Register Access */
#define SAIDA_VEL_BIT_MASK               (* (reg8 *) SAIDA_VEL__BIT_MASK)
/* Bypass Enable */
#define SAIDA_VEL_BYP                    (* (reg8 *) SAIDA_VEL__BYP)
/* Port wide control signals */                                                   
#define SAIDA_VEL_CTL                    (* (reg8 *) SAIDA_VEL__CTL)
/* Drive Modes */
#define SAIDA_VEL_DM0                    (* (reg8 *) SAIDA_VEL__DM0) 
#define SAIDA_VEL_DM1                    (* (reg8 *) SAIDA_VEL__DM1)
#define SAIDA_VEL_DM2                    (* (reg8 *) SAIDA_VEL__DM2) 
/* Input Buffer Disable Override */
#define SAIDA_VEL_INP_DIS                (* (reg8 *) SAIDA_VEL__INP_DIS)
/* LCD Common or Segment Drive */
#define SAIDA_VEL_LCD_COM_SEG            (* (reg8 *) SAIDA_VEL__LCD_COM_SEG)
/* Enable Segment LCD */
#define SAIDA_VEL_LCD_EN                 (* (reg8 *) SAIDA_VEL__LCD_EN)
/* Slew Rate Control */
#define SAIDA_VEL_SLW                    (* (reg8 *) SAIDA_VEL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SAIDA_VEL_PRTDSI__CAPS_SEL       (* (reg8 *) SAIDA_VEL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SAIDA_VEL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SAIDA_VEL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SAIDA_VEL_PRTDSI__OE_SEL0        (* (reg8 *) SAIDA_VEL__PRTDSI__OE_SEL0) 
#define SAIDA_VEL_PRTDSI__OE_SEL1        (* (reg8 *) SAIDA_VEL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SAIDA_VEL_PRTDSI__OUT_SEL0       (* (reg8 *) SAIDA_VEL__PRTDSI__OUT_SEL0) 
#define SAIDA_VEL_PRTDSI__OUT_SEL1       (* (reg8 *) SAIDA_VEL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SAIDA_VEL_PRTDSI__SYNC_OUT       (* (reg8 *) SAIDA_VEL__PRTDSI__SYNC_OUT) 


#if defined(SAIDA_VEL__INTSTAT)  /* Interrupt Registers */

    #define SAIDA_VEL_INTSTAT                (* (reg8 *) SAIDA_VEL__INTSTAT)
    #define SAIDA_VEL_SNAP                   (* (reg8 *) SAIDA_VEL__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SAIDA_VEL_H */


/* [] END OF FILE */
