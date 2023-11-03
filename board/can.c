/*
 * bsp_flexcan.c
 *
 *  Created on: 31 oct. 2023
 *      Author: PLANTIUM
 */
#include <can.h>
#include "peripherals.h"
#include "fsl_debug_console.h"

#define TX_MESSAGE_BUFFER_NUM (2)
#define RX_MESSAGE_BUFFER_NUM (1)
#define TS_CAN CAN2

flexcan_handle_t flexcanHandle;
uint32_t txIdentifier;
uint32_t rxIdentifier;
volatile bool txComplete = false;
flexcan_mb_transfer_t txXfer, rxXfer;
flexcan_frame_t frame,can2_rxframe;
volatile bool rxComplete = false;

uint8_t CAN_Send_Msg(uint8_t* msg,uint8_t len)
{
	uint8_t ret=0;

	frame.format=kFLEXCAN_FrameFormatExtend;
	frame.type=kFLEXCAN_FrameTypeData;
	frame.id=FLEXCAN_ID_EXT(0x18FFF6E6);
	frame.length=len;

	frame.dataByte0=msg[0];
	frame.dataByte1=msg[1];
	frame.dataByte2=msg[2];
	frame.dataByte3=msg[3];
	frame.dataByte4=msg[4];
	frame.dataByte5=msg[5];
	frame.dataByte6=msg[6];
	frame.dataByte7=msg[7];

	if(FLEXCAN_TransferSendBlocking(TS_CAN,TX_MESSAGE_BUFFER_NUM,&frame)==kStatus_Success) ret=0;
	else ret=1;

	return ret;
}

uint8_t CAN_Receive_Msg(uint8_t *buf)
{
	uint8_t datalen=0;
	if(rxComplete==true)
	{
		rxComplete=false;

		buf[0]=can2_rxframe.dataByte0;
		buf[1]=can2_rxframe.dataByte1;
		buf[2]=can2_rxframe.dataByte2;
		buf[3]=can2_rxframe.dataByte3;
		buf[4]=can2_rxframe.dataByte4;
		buf[5]=can2_rxframe.dataByte5;
		buf[6]=can2_rxframe.dataByte6;
		buf[7]=can2_rxframe.dataByte7;
		datalen=can2_rxframe.length;
	}
	else
		datalen=0;

	return datalen;
}

void CAN_ProcessIRQ(void)
{
	if (FLEXCAN_GetMbStatusFlags(TS_CAN,1<<RX_MESSAGE_BUFFER_NUM))
	{
		FLEXCAN_ClearMbStatusFlags(CAN2,1<<RX_MESSAGE_BUFFER_NUM);
		FLEXCAN_ReadRxMb(TS_CAN,RX_MESSAGE_BUFFER_NUM,&can2_rxframe);

		if(can2_rxframe.id == FLEXCAN_RX_MB_EXT_MASK(0x18FFF680, 0, 0))
		{
			rxComplete=true;
		}
	}
	__DSB();
}

void BOARD_CAN2_FLEXCAN_IRQHANDLER(void)
{
	CAN_ProcessIRQ();
}
