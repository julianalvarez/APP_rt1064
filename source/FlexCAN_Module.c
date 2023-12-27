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
/* Include ********************************************************************/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "fsl_debug_console.h"
#include "can_ext.h"
#include "FlexCAN_Module.h"
#include "include/j1939.h"
#include "time.h"
#include "fsl_adc.h"

/* TODO: insert other include files here. */
/* TODO: insert other definitions and declarations here. */

/* Prototypes *****************************************************************/
uint8_t mode = MODE_AT_START;

CAN_msg msgRx;
int i = 0 ;
ABGC_MSG_T                          tABGC;        /* TP */
static uint8_t      primaryBus = 0;

double valueADC_ch0_V = 0;
double valueADC_ch1_V = 0;

void CAN_send_Msg(uint32_t ctrl);

/* Functions ******************************************************************/
int main(void) {
    /* Init board hardware. */
    BOARD_ConfigMPU();

    CLOCK_EnableClock(kCLOCK_Iomuxc);

    BOARD_InitPins_UART1();

    BOARD_InitPins_ADC1();
    BOARD_InitBootClocks();
    BOARD_InitUART();
    TIME_Init(1000U);
    /* CANx - Open J1939 */
	Open_J1939 (0,                             /* Controller            */
				true,                               /* Init Name and Address */
				0xE6,                      /* Address               */
				ARBITRARY_ADDRESS_NOT_SUPPORTED,    /* ARBITRARY_ADDRESS     */
				INDUSTRY_GROUP_AGRICULTURAL,        /* INDUSTRY_GROUP        */
				VEHICLE_INSTANCE_NA,                /* VEHICLE_INSTANCE      */
				VEHICLE_SYSTEM_AGRICULTURAL_TRACTOR,/* VEHICLE_SYSTEM        */
				FUNCTION_STEERING_CONTROLLER,       /* FUNCTION              */
				0,                      /* FUNCTION_INSTANCE     */
				ECU_INSTANCE_NA,                    /* ECU_INSTANCE          */
				MANUFACTURER_CODE_GENTEC,           /* MANUFACTURER_CODE     */
				32);                      /* IDENTITY_NUMBER       */


#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    CANMSG_ABGC_Init(0x0);
    PRINTF("Init CAN2\r\n");
    /* Enter an infinite loop*/
    while(1){

    	ADC_SetChannelConfig(BOARD_ADC1_PERIPHERAL, BOARD_ADC1_CH0_CONTROL_GROUP, &BOARD_ADC1_channels_config[0]);
    	valueADC_ch0_V = ADC_GetChannelConversionValue(BOARD_ADC1_PERIPHERAL, 0U) * 3.3 / 4095;
    	ADC_SetChannelConfig(BOARD_ADC1_PERIPHERAL, BOARD_ADC1_CH0_CONTROL_GROUP, &BOARD_ADC1_channels_config[1]);
    	valueADC_ch1_V = ADC_GetChannelConversionValue(BOARD_ADC1_PERIPHERAL, 0U) * 3.3 / 4095;

		PRINTF("%.3fV  %.3fV\r\n", valueADC_ch0_V, valueADC_ch1_V);
    	Processor_J1939();
    	mode = msgRx.data[0] == 1 ? MODE_PERIODIC : MODE_AT_START;
    	if(mode == MODE_PERIODIC){
    			CAN_send_Msg(0);
    	}

		for (i = 0; i < 4000000U; i++)
		{
			__ASM("nop");
		}

    }
    return 0 ;
}
void CAN_send_Msg(uint32_t ctrl)
{
    tABGC.mode = msgRx.data[0];
    tABGC.dato1 = msgRx.data[1];
    tABGC.dato2 = msgRx.data[2];
    tABGC.dato3 = msgRx.data[3];
    tABGC.dato4 = msgRx.data[4];
    tABGC.dato5 = msgRx.data[5];
    tABGC.dato6 = msgRx.data[6];
    tABGC.dato7 = msgRx.data[7];

    Output_J1939 (	ctrl,
    				0xFFF6U,
			        J1939_INFO_PRIORITY,
					J1939_DATA_LENGTH,
                    &tABGC,
                    J1939_Address[ctrl]);

}

void CANMSG_ABGC_Init(uint8_t primary)
{
    int32_t             result;

    primaryBus = primary;

    /* PGN 0xFFF4 ABGC_cansg AB General Curve */
    result = OnPgn_J1939 (primaryBus,
    					  0xFFF6U,
                          8U,
                          &tABGC,
                          PAT_GEN_OnABGC,
                          0, /* Disabled */
                          NULL);
    if (result != RC_SUCCESS) {
    	PRINTF("Error Registering Message\n");
    }
}

uint32_t PAT_GEN_OnABGC (uint32_t Addr)
{
	msgRx.data[0] = tABGC.mode;
	msgRx.data[1] = tABGC.dato1;
	msgRx.data[2] = tABGC.dato2;
	msgRx.data[3] = tABGC.dato3;
	msgRx.data[4] = tABGC.dato4;
	msgRx.data[5] = tABGC.dato5;
	msgRx.data[6] = tABGC.dato6;
	msgRx.data[7] = tABGC.dato7;

	if (msgRx.data[0] == 0){
		CAN_send_Msg(0);
	}
	return 0;
}
