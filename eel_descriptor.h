/*******************************************************************************
* Library       : EEPROM Emulation Library (T01)
*
* File Name     : eel_descriptor.h
* Lib. Version  : V1.13 (for CC-RL)
* Device(s)     : RL78
* Description   : user configurable parameter of the EEPROM emulation
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

#ifndef __EEL_DESCRIPTOR_H_INCLUDED
#define __EEL_DESCRIPTOR_H_INCLUDED


/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
/* empty */


/*==============================================================================================*/
/* constant definitions   (USER CONFIGURABLE PART)                                                                      */
/*==============================================================================================*/


/* specifies the flash access library used for EEPROM emulation               */
/* Use 'D' for data-flash, 'C' for code-flash. Other values are invalid       */
#define   EEL_STORAGE_TYPE              'D'


/* specifies the number of abstract variables the EEL should handle           */
#define   EEL_VAR_NO                    8


/* Maximum size of the active area expressed in blocks  */
/* Overrunning this threshold triggers automatically the refresh process effecting the last active block */
#define   EEL_REFRESH_BLOCK_THRESHOLD   1


#endif
