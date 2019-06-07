/*******************************************************************************
* Library       : EEPROM Emulation Library (T01)
*
* File Name     : eel_descriptor.c
* Lib. Version  : V1.13 (for CC-RL)
* Device(s)     : RL78
* Description   : user defined EEL-variable descriptor
*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2015, 2016 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/

/*==============================================================================================*/
/* compiler settings                                                                            */
/*==============================================================================================*/
/* empty */


/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
#include  "eel_types.h"
#include  "eel_descriptor.h"

#if (EEL_STORAGE_TYPE == 'C')
  #include  "fcl_types.h"
#elif (EEL_STORAGE_TYPE=='D')
  #include  "fdl_types.h"
#else
  #error "EEL: wrong storage type defined !"
#endif


/* definition of variable types registered at EEL */
#include  "EEL_user_types.h"


/*==============================================================================================*/
/* import list                                                                                  */
/*==============================================================================================*/
/* empty */


/*==============================================================================================*/
/* data definition                                                                              */
/*==============================================================================================*/
/* constant segment definition */
#pragma section bss EEL_UDAT

#if (EEL_STORAGE_TYPE=='C')
  eel_u16   EEL_var_ref[EEL_VAR_NO];
#else
  eel_u16   EEL_var_ref[1];                                    /* dummy address for FDL variant */
#endif



/* constant segment definition */
#pragma section const EEL_CNST

/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      B E G I N    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A      *******/
/*******                                                                                           *******/
/*********************************************************************************************************/

__far const eel_u08 eel_descriptor[EEL_VAR_NO+1][4] =
            {
              /* identifier,             word-size (1...64),                                             */
              /* byte-size (1..255),     RAM-Ref.                                                        */
              /* --------------------------------------------------------------------------------------- */
              { (eel_u08)'a',            (eel_u08)((sizeof(type_A)+3U)/4U), \
                (eel_u08)sizeof(type_A), (eel_u08)(0x01) }, \
              { (eel_u08)'b',            (eel_u08)((sizeof(type_B)+3U)/4U), \
                (eel_u08)sizeof(type_B), (eel_u08)(0x01) }, \
              { (eel_u08)'c',            (eel_u08)((sizeof(type_C)+3U)/4U), \
                (eel_u08)sizeof(type_C), (eel_u08)(0x01) }, \
              { (eel_u08)'d',            (eel_u08)((sizeof(type_D)+3U)/4U), \
                (eel_u08)sizeof(type_D), (eel_u08)(0x01) }, \
              { (eel_u08)'e',            (eel_u08)((sizeof(type_E)+3U)/4U), \
                (eel_u08)sizeof(type_E), (eel_u08)(0x01) }, \
              { (eel_u08)'f',            (eel_u08)((sizeof(type_F)+3U)/4U), \
                (eel_u08)sizeof(type_F), (eel_u08)(0x01) }, \
              { (eel_u08)'x',            (eel_u08)((sizeof(type_X)+3U)/4U), \
                (eel_u08)sizeof(type_X), (eel_u08)(0x01) }, \
              { (eel_u08)'z',            (eel_u08)((sizeof(type_Z)+3U)/4U), \
                (eel_u08)sizeof(type_Z), (eel_u08)(0x01) }, \
              { (eel_u08)(0x00),         (eel_u08)(0x00), \
                (eel_u08)(0x00),         (eel_u08)(0x00) }, \
            };

/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      E N D    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A          *******/
/*******                                                                                           *******/
/*********************************************************************************************************/





/* ----------------------------------------------------------------------------------------------------- */
/* ------                                                                                          ----- */
/* ------     B E G I N    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A       ----- */
/* ------                                                                                          ----- */
/* ----------------------------------------------------------------------------------------------------- */
__far const eel_u08   eel_refresh_bth_u08     = (eel_u08)EEL_REFRESH_BLOCK_THRESHOLD;
__far const eel_u08   eel_storage_type_u08    = (eel_u08)EEL_STORAGE_TYPE;
__far const eel_u08   eel_var_number_u08      = (eel_u08)EEL_VAR_NO;
/* ----------------------------------------------------------------------------------------------------- */
/* ------                                                                                          ----- */
/* ------     E N D    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A           ----- */
/* ------                                                                                          ----- */
/* ----------------------------------------------------------------------------------------------------- */
