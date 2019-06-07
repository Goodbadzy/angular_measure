/*******************************************************************************
* Library       : EEPROM Emulation Library (T01)
*
* File Name     : eel.h
* Lib. Version  : V1.13 (for CC-RL)
* Device(s)     : RL78
* Description   : API definition of the EEPROM Emulation Library T01 (EEL)
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

#ifndef __EEL_H_INCLUDED
#define __EEL_H_INCLUDED

/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
#include  "eel_types.h"


/*================================================================================================================*/
/* global function prototypes                                                                                     */
/*================================================================================================================*/



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Initialization of the EEPROM Emulation Library (EEL).                                           */
/*                Internal variables are initialized.                                                             */
/*  Input:        -                                                                                               */
/*  Output:       -                                                                                               */
/*  Return:       status: configuration related status code                                                       */
/*                - EEL_OK:                 initialization done without problems                                  */
/*                - EEL_ERR_CONFIGURATION:  pool configuration error                                              */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  eel_status_t __far EEL_Init(void);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Activates/Deactivates the access to the used flash medium.                                      */
/*                If data-flash (FDL) is used, the data-flash clock is switched ON/OFF.                           */
/*                In case of code-flash (FCL) is used, the FLMD0 pin is controlled herewith.                      */
/*  Input:        -                                                                                               */
/*  Output:       -                                                                                               */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void  __far EEL_Open(void);
extern  void  __far EEL_Close(void);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Starting of execution of the corresponding EEL request.                                         */
/*                The value of the time-out within the request variable determines the command execution mode.    */
/*                Time-Out=0x00  -> polling mode, returns immediately to the application.                         */
/*                Time-Out=0xFF  -> enforced mode, returns to the application after the command is completed.     */
/*                other values   -> counting mode, returns to the application after Time-Out was counted          */
/*                                  down to 0x00 or the command is completed before that.                         */
/*  Input:        request_pstr - pointer to the EEL request variable                                              */
/*  Output:       error: command related status code                                                              */
/*                - EEL_OK:             command completed without problems                                        */
/*                - EEL_BUSY:           command accepted and                                                      */
/*                - EEL_ERR_REJECTED:   specified command couldn't be accepted (driver busy with other comamnd)   */
/*                - other:              refer to the documentation.                                               */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void  __far  EEL_Execute(__near eel_request_t* request_pstr);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Normally, this function takes care for the execution of the background process (maintenance).   */
/*                When any command is started in "polling" mode, this function executes it state-by-state         */
/*                When any command is started in "counting" mode, this function executes it time-slice-wise.      */
/*                When starting commands in "enforced" mode, the EEL_Handler is not needed for command execution. */
/*                Just maintenance on EEL pool and data is realized by it in the idle-time of the application.    */
/*                                                                                                                */
/*  Input:        timeout - time-slice for the command execution expressed in time-out ticks                      */
/*                          0x00,  polling execution mode without TO supervision, execution state-by-state        */
/*                          other, allocates a time-slice for the EEL command execution                           */
/*  Output:       -                                                                                               */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void  __far  EEL_Handler(eel_u08 timeout_u08);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard functions                                                                              */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      This function decrements an internal 8-bit software counter used for timeout supervision.       */
/*                The time out period (time-slice) is determined by EEL_Execute(....) or EEL_Handler(...)         */
/*                EEL_TimeOut_CountDown() should be called in any periodical ISR creating the counting time-base. */
/*                Each time this function is called time-count register is decremented down to zero.              */
/*                When timeout-counter becomes 0x00 an internal timeout-event is generated, the counting          */
/*                process is stopped and program counter (PC) is returned from EEL to the user application.       */
/*                Preferable place for EEL_TimeOut_Count() the operating system timer is used for such purpose.   */
/*  Input:        -                                                                                               */
/*  Output:       -                                                                                               */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void      __far  EEL_TimeOut_CountDown(void);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Provides the internal status of the EEL.                                                        */
/*                The information is only valid if the returned status is EEL_OK.                                 */
/*  Input:        &eel_driver_pstr - address of the status variable used by the application                       */
/*  Output:       driverStatus_pstr->operationStatus_enu:   operation status of the EEL driver                    */
/*                  EEL_OPERATION_PASSIVE:  STARTUP command not yet executed successfully                         */
/*                  EEL_OPERATION_IDLE:     no command and no background process is being executed                */
/*                  EEL_OPERATION_BUSY:     a command or any background process is being executed                 */
/*                driverStatus_pstr->accessStatus_enu:      access status of the EEL driver                       */
/*                  EEL_ACCESS_LOCKED:      any access to the EEL is disabled                                     */
/*                  EEL_ACCESS_UNLOCKED:    any access to the EEL is possible (after successful startup)          */
/*                driverStatus_pstr->backgroundStatus_enu:  internal status of the background process             */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void      __far  EEL_GetDriverStatus(__near eel_driver_status_t* driverStatus_pstr);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Provides the currently available space inside the EEL pool.                                     */
/*                It consists of the space inside the active heading block and all "prepared" blocks in pool.     */
/*  Input:        &space_pu16 - address of the space variable used by the application                             */
/*  Output:       space_pu16  - available space expressed in flash words (here 1 word = 4 bytes)                  */
/*  Return:       status: returns the execution status of this function                                           */
/*                EEL_OK - space value is correct                                                                 */
/*                EEL_ERR_REJECTED - not able to calculate available space (space_pu16* remains unchanged)        */
/*                EEL_ERR_ACCESS_LOCKED - STARTUP not yet executed successfully                                   */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  eel_status_t  __far  EEL_GetSpace(__near eel_u16* space_pu16);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      This function returns the pointer to the "zero-terminated" version string of the library.       */
/*  Input:        -                                                                                               */
/*  Output:       -                                                                                               */
/*  Return:       address of the version string (pointer to the first character)                                  */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  __far  eel_u08*  __far  EEL_GetVersionString(void);


#endif
