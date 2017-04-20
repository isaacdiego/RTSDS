/*******************************************************************************
* File Name: PINO_PROCESSAMENTO.h  
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

#if !defined(CY_PINS_PINO_PROCESSAMENTO_H) /* Pins PINO_PROCESSAMENTO_H */
#define CY_PINS_PINO_PROCESSAMENTO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PINO_PROCESSAMENTO_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PINO_PROCESSAMENTO__PORT == 15 && ((PINO_PROCESSAMENTO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PINO_PROCESSAMENTO_Write(uint8 value) ;
void    PINO_PROCESSAMENTO_SetDriveMode(uint8 mode) ;
uint8   PINO_PROCESSAMENTO_ReadDataReg(void) ;
uint8   PINO_PROCESSAMENTO_Read(void) ;
uint8   PINO_PROCESSAMENTO_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PINO_PROCESSAMENTO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PINO_PROCESSAMENTO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PINO_PROCESSAMENTO_DM_RES_UP          PIN_DM_RES_UP
#define PINO_PROCESSAMENTO_DM_RES_DWN         PIN_DM_RES_DWN
#define PINO_PROCESSAMENTO_DM_OD_LO           PIN_DM_OD_LO
#define PINO_PROCESSAMENTO_DM_OD_HI           PIN_DM_OD_HI
#define PINO_PROCESSAMENTO_DM_STRONG          PIN_DM_STRONG
#define PINO_PROCESSAMENTO_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PINO_PROCESSAMENTO_MASK               PINO_PROCESSAMENTO__MASK
#define PINO_PROCESSAMENTO_SHIFT              PINO_PROCESSAMENTO__SHIFT
#define PINO_PROCESSAMENTO_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PINO_PROCESSAMENTO_PS                     (* (reg8 *) PINO_PROCESSAMENTO__PS)
/* Data Register */
#define PINO_PROCESSAMENTO_DR                     (* (reg8 *) PINO_PROCESSAMENTO__DR)
/* Port Number */
#define PINO_PROCESSAMENTO_PRT_NUM                (* (reg8 *) PINO_PROCESSAMENTO__PRT) 
/* Connect to Analog Globals */                                                  
#define PINO_PROCESSAMENTO_AG                     (* (reg8 *) PINO_PROCESSAMENTO__AG)                       
/* Analog MUX bux enable */
#define PINO_PROCESSAMENTO_AMUX                   (* (reg8 *) PINO_PROCESSAMENTO__AMUX) 
/* Bidirectional Enable */                                                        
#define PINO_PROCESSAMENTO_BIE                    (* (reg8 *) PINO_PROCESSAMENTO__BIE)
/* Bit-mask for Aliased Register Access */
#define PINO_PROCESSAMENTO_BIT_MASK               (* (reg8 *) PINO_PROCESSAMENTO__BIT_MASK)
/* Bypass Enable */
#define PINO_PROCESSAMENTO_BYP                    (* (reg8 *) PINO_PROCESSAMENTO__BYP)
/* Port wide control signals */                                                   
#define PINO_PROCESSAMENTO_CTL                    (* (reg8 *) PINO_PROCESSAMENTO__CTL)
/* Drive Modes */
#define PINO_PROCESSAMENTO_DM0                    (* (reg8 *) PINO_PROCESSAMENTO__DM0) 
#define PINO_PROCESSAMENTO_DM1                    (* (reg8 *) PINO_PROCESSAMENTO__DM1)
#define PINO_PROCESSAMENTO_DM2                    (* (reg8 *) PINO_PROCESSAMENTO__DM2) 
/* Input Buffer Disable Override */
#define PINO_PROCESSAMENTO_INP_DIS                (* (reg8 *) PINO_PROCESSAMENTO__INP_DIS)
/* LCD Common or Segment Drive */
#define PINO_PROCESSAMENTO_LCD_COM_SEG            (* (reg8 *) PINO_PROCESSAMENTO__LCD_COM_SEG)
/* Enable Segment LCD */
#define PINO_PROCESSAMENTO_LCD_EN                 (* (reg8 *) PINO_PROCESSAMENTO__LCD_EN)
/* Slew Rate Control */
#define PINO_PROCESSAMENTO_SLW                    (* (reg8 *) PINO_PROCESSAMENTO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PINO_PROCESSAMENTO_PRTDSI__CAPS_SEL       (* (reg8 *) PINO_PROCESSAMENTO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PINO_PROCESSAMENTO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PINO_PROCESSAMENTO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PINO_PROCESSAMENTO_PRTDSI__OE_SEL0        (* (reg8 *) PINO_PROCESSAMENTO__PRTDSI__OE_SEL0) 
#define PINO_PROCESSAMENTO_PRTDSI__OE_SEL1        (* (reg8 *) PINO_PROCESSAMENTO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PINO_PROCESSAMENTO_PRTDSI__OUT_SEL0       (* (reg8 *) PINO_PROCESSAMENTO__PRTDSI__OUT_SEL0) 
#define PINO_PROCESSAMENTO_PRTDSI__OUT_SEL1       (* (reg8 *) PINO_PROCESSAMENTO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PINO_PROCESSAMENTO_PRTDSI__SYNC_OUT       (* (reg8 *) PINO_PROCESSAMENTO__PRTDSI__SYNC_OUT) 


#if defined(PINO_PROCESSAMENTO__INTSTAT)  /* Interrupt Registers */

    #define PINO_PROCESSAMENTO_INTSTAT                (* (reg8 *) PINO_PROCESSAMENTO__INTSTAT)
    #define PINO_PROCESSAMENTO_SNAP                   (* (reg8 *) PINO_PROCESSAMENTO__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PINO_PROCESSAMENTO_H */


/* [] END OF FILE */
