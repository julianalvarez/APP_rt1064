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
/* TODO: insert other include files here. */
#include "bsp_flexcan.h"
/* TODO: insert other definitions and declarations here. */
uint8_t cnt=0;
uint8_t canbuf[8];
uint8_t rx_canbuf[8];
uint8_t res;
/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\r\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1){
		res=0;

		res=CAN2_Receive_Msg(rx_canbuf);
		if(res)
		{
			PRINTF("\r\n RECEIVE\r\n");
			for(i=0;i<res;i++){
				PRINTF("%x",rx_canbuf[i]);
				PRINTF("\r\n");
			}

		}

		for(i=0;i<8;i++)
		{
			canbuf[i]=cnt+i;
		}
		res=CAN2_Send_Msg(canbuf,8);
		if(!res)
			PRINTF("SEND OK\r\n");
		else
			PRINTF("SEND ERROR\r\n");

		for (i = 0; i < 40000000U; i++)
		{
			__ASM("nop");
		}

    }
    return 0 ;
}
