/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_port.c
* Version      : CodeGenerator for RL78/F13 V2.03.03.01 [28 Oct 2018]
* Device(s)    : R5F10BGG
* Tool-Chain   : CCRL
* Description  : This file implements device driver for PORT module.
* Creation Date: 7/6/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#define PMC7         (*(volatile __near unsigned char  *)0x67)
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    P0 = _01_Pn0_OUTPUT_1;
    P1 = _01_Pn0_OUTPUT_1 | _00_Pn2_OUTPUT_0;
    P6 = _00_Pn0_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _08_Pn3_OUTPUT_1;
    //PSRSEL = _00_PSR12_NORMAL | _00_PSR10_NORMAL;
    PM0 = _00_PMn0_MODE_OUTPUT | _FE_PM0_DEFAULT;
    PM1 = _00_PMn0_MODE_OUTPUT | _02_PMn1_MODE_INPUT | _00_PMn2_MODE_OUTPUT | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE |
          _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;
    PM6 = _00_PMn0_MODE_OUTPUT | _02_PMn1_MODE_INPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM6_DEFAULT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
