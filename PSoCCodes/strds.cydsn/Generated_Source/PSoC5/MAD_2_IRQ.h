/*******************************************************************************
* File Name: MAD_2_IRQ.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_MAD_2_IRQ_H)
#define CY_ISR_MAD_2_IRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void MAD_2_IRQ_Start(void);
void MAD_2_IRQ_StartEx(cyisraddress address);
void MAD_2_IRQ_Stop(void);

CY_ISR_PROTO(MAD_2_IRQ_Interrupt);

void MAD_2_IRQ_SetVector(cyisraddress address);
cyisraddress MAD_2_IRQ_GetVector(void);

void MAD_2_IRQ_SetPriority(uint8 priority);
uint8 MAD_2_IRQ_GetPriority(void);

void MAD_2_IRQ_Enable(void);
uint8 MAD_2_IRQ_GetState(void);
void MAD_2_IRQ_Disable(void);

void MAD_2_IRQ_SetPending(void);
void MAD_2_IRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the MAD_2_IRQ ISR. */
#define MAD_2_IRQ_INTC_VECTOR            ((reg32 *) MAD_2_IRQ__INTC_VECT)

/* Address of the MAD_2_IRQ ISR priority. */
#define MAD_2_IRQ_INTC_PRIOR             ((reg8 *) MAD_2_IRQ__INTC_PRIOR_REG)

/* Priority of the MAD_2_IRQ interrupt. */
#define MAD_2_IRQ_INTC_PRIOR_NUMBER      MAD_2_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable MAD_2_IRQ interrupt. */
#define MAD_2_IRQ_INTC_SET_EN            ((reg32 *) MAD_2_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the MAD_2_IRQ interrupt. */
#define MAD_2_IRQ_INTC_CLR_EN            ((reg32 *) MAD_2_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the MAD_2_IRQ interrupt state to pending. */
#define MAD_2_IRQ_INTC_SET_PD            ((reg32 *) MAD_2_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the MAD_2_IRQ interrupt. */
#define MAD_2_IRQ_INTC_CLR_PD            ((reg32 *) MAD_2_IRQ__INTC_CLR_PD_REG)


#endif /* CY_ISR_MAD_2_IRQ_H */


/* [] END OF FILE */
