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
#include "FlexCAN_Module.h"

/* TODO: insert other include files here. */
/* TODO: insert other definitions and declarations here. */

/* Prototypes *****************************************************************/

int8_t status;
static uint8_t data;
static uint8_t s_nor_read_buffer[1];
uint8_t *buff;

uint8_t mode = MODE_AT_START;
CAN_msg msgRx;
int i = 0 ;
ABGC_MSG_T                          tABGC;        /* TP */
static uint8_t      primaryBus = 0;

double valueADC_ch0_V = 0;
double valueADC_ch9_V = 0;

void CAN_send_Msg(uint32_t ctrl);

/* Functions ******************************************************************/
int main(void) {
    /* Init board hardware. */
    BOARD_ConfigMPU();

    CLOCK_Init();

    UART_Init();

    SPIFLASH_init();

    TIME_Init(1000U);

    HB_Init(2000);

    ADC_Iface_Init();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

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
    PRINTF("Init CAN2\r\n");

    CANMSG_ABGC_Init(0x0);

/*
    // Erase sectors.
    PRINTF("Erasing Serial NOR over FlexSPI...\r\n");
    status = SPIFLASH_erase_sector(BOARD_FLEXSPI, EXAMPLE_SECTOR * SECTOR_SIZE);
    if (status != kStatus_Success)
    {
        PRINTF("Erase sector failure !\r\n");
        return -1;
    }

    memset(s_nor_program_buffer, 0xFFU, sizeof(s_nor_program_buffer));

    DCACHE_InvalidateByRange(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE, FLASH_PAGE_SIZE);

    memcpy(s_nor_read_buffer, (void *)(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE),
           sizeof(s_nor_read_buffer));

    if (memcmp(s_nor_program_buffer, s_nor_read_buffer, sizeof(s_nor_program_buffer)))
    {
        PRINTF("Erase data -  read out data value incorrect !\r\n ");
        return -1;
    }
    else
    {
        PRINTF("Erase data - successfully. \r\n");
    }

    for (i = 0; i < 0x1U; i++)
    {
        program_buffer[i] = i;
    }
*/
    data = 4;
    status = SPIFLASH_WriteByte(BOARD_FLEXSPI, EXAMPLE_SECTOR * SECTOR_SIZE + 16, data);
    if (status != FLASH_COMPLETE)
    {
        PRINTF("Byte program failure !\r\n");
        return -1;
    }

    buff = (uint8_t *) 0x70080000 + 16;//0x70000000 + (0x1000 * 0x64) --> Byte 70064000

    if (status != kStatus_Success)
    {
        return status;
    }

    PRINTF("Valor del puntero: %d \r\n", *buff);

    msgRx.data[1] = 0;

    /* Enter an infinite loop*/
    while(1){
    	//valueADC_ch0_V = ADC_Get(1,0);
    	valueADC_ch9_V = CSTEER_GetWheelAngleVoltage();

		PRINTF("%.3fV \r\n", valueADC_ch9_V);
		HB_Set(msgRx.data[1],1);

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
