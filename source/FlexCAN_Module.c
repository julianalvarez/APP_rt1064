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

/* TODO: insert other include files here. */
/* TODO: insert other definitions and declarations here. */

uint8_t res;

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
		res=CAN_Receive_Msg(&msgRx);

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
	for(i=0;i<res;i++){
		msgTx.abData[i]=msgRx.data[i];
	}
	msgTx.bDlc = 8;
	msgTx.bXtd = kFLEXCAN_FrameFormatExtend;
	msgTx.dwId = 0x18FFF6E6;

	res = send_can_msg(0, 0, &msgTx);
	if(!res)
		PRINTF("SEND OK\r\n");
	else
		PRINTF("SEND ERROR\r\n");
}

