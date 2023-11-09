/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    FlexCAN_Module.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "fsl_debug_console.h"
#include "can_ext.h"
#include "FlexCAN_Module.h"

/* TODO: insert other include files here. */
/* TODO: insert other definitions and declarations here. */
uint8_t mode = MODE_AT_START;

uint8_t res = 0;

tSend msgTx;
CAN_msg msgRx;
int i = 0 ;
/*
 * @brief   Application entry point.
 */

void CAN_send_Msg(void);

int main(void) {

    /* Init board hardware. */
    BOARD_ConfigMPU();

    BOARD_Clock_Enable();
	BOARD_InitPinsLPUART();

    BOARD_InitBootClocks();
    BOARD_InitLPUART1();

    init_can(0, 0, 0, 0, 250000/1000);

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Init CAN2\r\n");

    /* Enter an infinite loop*/
    while(1){

    	switch(CAN_GetMode()){
    		case MODE_AT_START:
    			if(res)
    			{
    				CAN_send_Msg();
    			}
    			break;
    		case MODE_PERIODIC:
    			CAN_send_Msg();
    			break;
    		default:
    			break;
    	}

		for (i = 0; i < 40000000U; i++)
		{
			__ASM("nop");
		}

    }
    return 0 ;
}
void CAN_send_Msg(void)
{
	uint8_t err = 0;
	for(i=0;i<8;i++){
		msgTx.abData[i]=msgRx.data[i];
	}
	msgTx.bDlc = 8;
	msgTx.bXtd = kFLEXCAN_FrameFormatExtend;
	msgTx.dwId = 0x18FFF6E6;

	err = send_can_msg(0, 0, &msgTx);
	if(!err)
		PRINTF("SEND OK\r\n");
	else
		PRINTF("SEND ERROR\r\n");
}

void Obj_ISR (uint8_t ctrl, CAN_msg* Msg)
{
	res=0;
	if(Msg->id == FLEXCAN_RX_MB_EXT_MASK(0x18FFF680, 0, 0))
	{
		msgRx.data[0] = Msg->data[0];
		msgRx.data[1] = Msg->data[1];
		msgRx.data[2] = Msg->data[2];
		msgRx.data[3] = Msg->data[3];
		msgRx.data[4] = Msg->data[4];
		msgRx.data[5] = Msg->data[5];
		msgRx.data[6] = Msg->data[6];
		msgRx.data[7] = Msg->data[7];

		msgRx.format = Msg->format;
		msgRx.id = Msg->id;
		msgRx.len = Msg->len;
		res = 1;
		if(msgRx.data[0] == 1)
		{
			CAN_SetMode(MODE_PERIODIC);
		}
		else
		{
			CAN_SetMode(MODE_AT_START);
		}
	}

}

void CAN_SetMode (uint8_t value)
{
	mode = value;
}

uint8_t CAN_GetMode (void)
{
	return mode;
}
