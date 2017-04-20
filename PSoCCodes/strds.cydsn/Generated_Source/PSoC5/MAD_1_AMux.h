/*******************************************************************************
* File Name: MAD_1_AMux.h
* Version 1.60
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_MAD_1_AMux_H)
#define CY_AMUX_MAD_1_AMux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void MAD_1_AMux_Start(void);
# define MAD_1_AMux_Init() MAD_1_AMux_Start()
void MAD_1_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void MAD_1_AMux_Stop(void); */
/* void MAD_1_AMux_Select(uint8 channel); */
/* void MAD_1_AMux_Connect(uint8 channel); */
/* void MAD_1_AMux_Disconnect(uint8 channel); */
/* void MAD_1_AMux_DisconnectAll(void) */


/***************************************
*     Initial Parameter Constants
***************************************/

#define MAD_1_AMux_CHANNELS  2
#define MAD_1_AMux_MUXTYPE   1
#define MAD_1_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define MAD_1_AMux_NULL_CHANNEL  0xFFu
#define MAD_1_AMux_MUX_SINGLE   1
#define MAD_1_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if MAD_1_AMux_MUXTYPE == MAD_1_AMux_MUX_SINGLE
#if !MAD_1_AMux_ATMOSTONE
# define MAD_1_AMux_Connect(channel) MAD_1_AMux_Set(channel)
#endif
# define MAD_1_AMux_Disconnect(channel) MAD_1_AMux_Unset(channel)
#else
#if !MAD_1_AMux_ATMOSTONE
void MAD_1_AMux_Connect(uint8 channel) ;
#endif
void MAD_1_AMux_Disconnect(uint8 channel) ;
#endif

#if MAD_1_AMux_ATMOSTONE
# define MAD_1_AMux_Stop() MAD_1_AMux_DisconnectAll()
# define MAD_1_AMux_Select(channel) MAD_1_AMux_FastSelect(channel)
void MAD_1_AMux_DisconnectAll(void) ;
#else
# define MAD_1_AMux_Stop() MAD_1_AMux_Start()
void MAD_1_AMux_Select(uint8 channel) ;
# define MAD_1_AMux_DisconnectAll() MAD_1_AMux_Start()
#endif

#endif /* CY_AMUX_MAD_1_AMux_H */


/* [] END OF FILE */
