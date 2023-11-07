/*
 * can_ext.c
 *
 *  Created on: 7 nov. 2023
 *      Author: PLANTIUM
 */

#include <can_ext.h>
#include "peripherals.h"
#include "can.h"

#define TX_MESSAGE_BUFFER_NUM (2)
#define RX_MESSAGE_BUFFER_NUM (1)
#define TS_CAN CAN2

flexcan_frame_t frame;

int32_t init_can (uint8_t bBusNumber,uint16_t wGlobMask,
								  uint32_t dwGlobMask,uint32_t dwGlobMaskLastmsg,
								  uint16_t wBitrate)
{
	if(bBusNumber == 0){
		BOARD_InitPinsFlexCAN();
		BOARD_InitFLEXCAN(wBitrate);
	}
	else{
		//completar para otro periferico CAN
	}

	return (CAN_NO_ERR);
}


int32_t send_can_msg (uint8_t bBusNumber,uint8_t bMsgObj, tSend *ptSend )
{
	uint8_t ret=0;

	frame.format=ptSend->bXtd;
	frame.type=kFLEXCAN_FrameTypeData;
	frame.id=FLEXCAN_ID_EXT(0x18FFF6E6);
	frame.length=ptSend->bDlc;

	frame.dataByte0=ptSend->abData[0];
	frame.dataByte1=ptSend->abData[1];
	frame.dataByte2=ptSend->abData[2];
	frame.dataByte3=ptSend->abData[3];
	frame.dataByte4=ptSend->abData[4];
	frame.dataByte5=ptSend->abData[5];
	frame.dataByte6=ptSend->abData[6];
	frame.dataByte7=ptSend->abData[7];

	if(bBusNumber == 0)
	{
		if(FLEXCAN_TransferSendBlocking(TS_CAN,TX_MESSAGE_BUFFER_NUM,&frame)==kStatus_Success) ret=0;
		else ret=1;
	}
	else{
		//Completar para otro periferico CAN
	}


	return ret;
}
