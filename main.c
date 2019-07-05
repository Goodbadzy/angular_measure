/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* code generator include */
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_adc.h"
#include "r_cg_wdt.h"
#include "r_cg_serial.h"
#include "r_rl78_can_drv.h"
//#include "r_rl78_can_sfr.h"

/* eeprom library include */
#include "eel.h"
#include "eel_types.h"
#include "eel_descriptor.h"
#include "eel_user_types.h"
#include "fdl.h"
#include "fdl_types.h"
#include "fdl_descriptor.h"

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
extern __far const fal_descriptor_t  fal_descriptor_str;
fal_status_t	my_fal_status;
eel_request_t	 my_eel_request;
eel_status_t     my_eel_status; 
eel_driver_status_t     my_eel_driver_status_str;

type_Z my_data = {0x00};
type_Z my_data_verify = {0x00};

/* adc result variable */
uint16_t GulAdcResultBuf[10];
uint8_t GulCsi0SendBuf[2] = {0x55,0xaa};
uint8_t GulCsi0RevBuf[10];

/* can related variable */
/*****************************************************************************/
unsigned char CANTraStandData[16]={
	//CiTBpA
	0x18,							//IDE ,RTR ,THDSE,ID28,ID27,ID26,ID25,ID24
	0x00,							//ID23,ID22,ID21, ID20,ID19,ID18,ID17,ID16
	0x00,							//ID15,ID14,ID13, ID12,ID11,ID10,ID09,ID08
	0x00,							//ID07,ID06,ID05, ID04,ID03,ID02,ID01,ID00
	//CiTBpB
	0x00,							//DLC3,DLC2,DLC1, DLC0,----,----,----,----
	0x00,							//LBL7,LBL6,LBL5, LBL4,LBL3,LBL2,LBL1,LBL0
	0x00,							//----,----,----,-----,----,----,----,----
	0x80,							//----,----,----,-----,----,----,----,----
	//CiTBpC
	0x55,							//DB0
	0x55,							//DB1
	0x55,							//DB2
	0x55,							//DB3
	//CiTBpD
	0x55,							//DB4
	0x55,							//DB5
	0x55,							//DB6
	0x55,							//DB7
	};

volatile can_frame_sfr_t can_txbuf[1] = {
 /*IDL,   IDH,   TS,    PTR,   DF0,   DF1,   DF2,   DF3   */
  {0x004c,0x0000,0x0000,0x7000,0x5555,0x5555,0xaaaa,0xaaaa}
};

volatile can_frame_sfr_t can_rxbuf[1];
uint8_t can_rbuf_index[1];

Can_RtnType can_rty;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
void MyErrorHandler(void)
{
    while(1);
}

void R_Systeminit(void)
{
    /* Set periperal I/O redirection */
    /* for real board */
	PIOR0 = 0xDFU;
    PIOR1 = 0xDFU;
    PIOR4 = 0x1FU;
    PIOR5 = 0x09U;
    PIOR7 = 0x00U;
	
	/* for demo board */
	//PIOR0 = 0xDFU;
    //PIOR1 = 0xDFU;
    //PIOR4 = 0x5FU;
    //PIOR5 = 0x09U;
    //PIOR7 = 0x00U;
	
    R_CGC_Get_ResetSource();
    R_CGC_Create();
    R_PORT_Create();
	R_SAU0_Create();
	R_CSI00_Create();
    R_ADC_Create();
	R_CAN_Create();
    //R_WDT_Create();

    /* Set invalid memory access detection control */
    //IAWCTL = 0x00U;
}

/*******************************************************************************
**                      Main                                                  **
*******************************************************************************/
void main(void)
{
	unsigned short i;

	/*=========================================================
	  Initialization
	  ========================================================*/
	R_Systeminit();
	
	/*=========================================================
	PORT TEST CASE
	========================================================*/
	//P1 = 0xff;
	//P1 = 0x00;
	
	/*=========================================================
	CSI TEST CASE
	========================================================*/	
	R_CSI00_Start();
	R_CSI00_Send_Receive(&GulCsi0SendBuf[0],2,&GulCsi0RevBuf[0]);
	
	/*=========================================================
	  ADC TEST CASE
	  ========================================================*/
	/* Enable ADC : ADCE = 1 */
	R_ADC_Set_OperationOn();
	  
	/* Wirte data to z identifier */ 
	for(i=0;i<0xffff;i++){my_data[0] = i;}; /* Delay by hand */
	
	/* Start ADC operation on : ADCS = 1 */	
	R_ADC_Start();
	
	for(i=0;i<0xffff;i++){my_data[0] = i;}; /* Delay by hand */

	R_ADC_Get_Result(&GulAdcResultBuf[0]);
	
	/*=========================================================
	  CAN TEST CASE
	  ========================================================*/
	/* Initialization of CAN */
	R_CAN_Init();
	
	/* Mode Switch */
	R_CAN_GlobalStart(); /* start global operation mode */
	R_CAN_ChStart_CH0(); /* start channel operation mode */
	
	for(i=0;i<0xffff;i++){my_data[0] = i;}; /* Delay by hand */

	/* Recevier */
	can_rty = CAN_RTN_BUFFER_EMPTY;
	while(CAN_RTN_BUFFER_EMPTY == can_rty){
		can_rty = R_CAN_ReadRxBuffer(&can_rbuf_index[0],(can_frame_sfr_t *)can_rxbuf);
	}
	
	/* Send CAN message */
	while(1){
	R_CAN_TrmByTxBuf_CH0(0,(const can_frame_sfr_t *)can_txbuf);
	}
	  
	/*=========================================================
	  EEPROM TEST CASE
	  ========================================================*/
	/* Init FAL */
	my_fal_status = FAL_Init(&fal_descriptor_str);
	if (my_fal_status != FAL_OK) 
	{
		MyErrorHandler();
	}
	
	/* Init EEL */	
	my_eel_status = EEL_Init();
	if (my_eel_status != EEL_OK) 
  	{ 
     	MyErrorHandler(); 
 	} 
	EEL_Open();
	
	/* Execute STARTUP if not already done */ 
	EEL_GetDriverStatus(&my_eel_driver_status_str);
	if(my_eel_driver_status_str.operationStatus_enu == EEL_OPERATION_PASSIVE) 
	{ 
  		my_eel_request.command_enu      = EEL_CMD_STARTUP; 
  		EEL_Execute(&my_eel_request); 
		do
		{
			EEL_Handler(0);
		}
		while (my_eel_request.status_enu == EEL_BUSY);
	}
	while(my_eel_request.status_enu != EEL_OK)
	{
		my_eel_request.command_enu	= EEL_CMD_FORMAT;
		EEL_Execute(&my_eel_request);
		do
		{
			EEL_Handler(0);
		}
		while (my_eel_request.status_enu == EEL_BUSY);
		if(my_eel_request.status_enu != EEL_OK)	
		{
			MyErrorHandler();
		}
		
		/* STARTUP command must be executed again */
		my_eel_request.command_enu 	= EEL_CMD_STARTUP;
		EEL_Execute(&my_eel_request);
		do
		{
			EEL_Handler(0);
		}
		while (my_eel_request.status_enu == EEL_BUSY);
		if (my_eel_request.status_enu != EEL_OK)
		{
			MyErrorHandler();
		}
	}
	
	/* Wirte data to z identifier */ 
	for(i=0;i<255;i++)
	{
		my_data[i] = i;
	}
	my_eel_request.address_pu08     = (__near eel_u08*)&my_data[0]; 
 	my_eel_request.identifier_u08	= 'z';
	my_eel_request.command_enu		= EEL_CMD_WRITE;
	EEL_Execute(&my_eel_request);
	do
	{
		EEL_Handler(0);
		EEL_GetDriverStatus(&my_eel_driver_status_str);
	}
	while ((my_eel_request.status_enu == EEL_BUSY) &&    \
	       (my_eel_driver_status_str.operationStatus_enu != EEL_OPERATION_IDLE));
	if (my_eel_request.status_enu != EEL_OK)
	{
		MyErrorHandler();
	}
	
	/* Read "z" data */
	my_eel_request.address_pu08   = (__near eel_u08*)&my_data_verify[0];  
	my_eel_request.identifier_u08 = 'z';
	my_eel_request.command_enu    = EEL_CMD_READ;   
	EEL_Execute(&my_eel_request);
	do
	{
		EEL_Handler(0);
	}
	while (my_eel_request.status_enu == EEL_BUSY);
	if (my_eel_request.status_enu != EEL_OK)
	{
		MyErrorHandler();
	}
	
	/* Close */	
	FAL_Close();
	EEL_Close();
	while(1)
	{
		__nop();
	}
	
}

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/













