/*
 * can_ext.c
 *
 *  Created on: 7 nov. 2023
 *      Author: PLANTIUM
 */

#include <can_ext.h>
#include "can.h"
#include "pin_mux.h"
#include <string.h>


flexcan_frame_t frame;
flexcan_frame_t can2_rxframe;
volatile bool rxComplete = false;

uint8_t mode = MODE_AT_START;

void CAN_rdMsg (uint32_t ctrl, CAN_msg *msg);
void CAN_ProcessIRQ(void);

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
	CAN_msg CanToSend;

    if (bBusNumber >= CAN_MAX_BUS_NR) {
        return (CAN_RANGE_ERR);
    }

    CanToSend.format = ptSend->bXtd;
    CanToSend.len    = ptSend->bDlc;
    CanToSend.id     = ptSend->dwId;

    memcpy (CanToSend.data, ptSend->abData, ptSend->bDlc);

	CAN_wrMsg(0, &CanToSend);

	return CAN_NO_ERR;
}
void CAN_rdMsg (uint32_t ctrl, CAN_msg *msg)
{
	if (ctrl == 0){
		msg->data[0]=can2_rxframe.dataByte0;
		msg->data[1]=can2_rxframe.dataByte1;
		msg->data[2]=can2_rxframe.dataByte2;
		msg->data[3]=can2_rxframe.dataByte3;
		msg->data[4]=can2_rxframe.dataByte4;
		msg->data[5]=can2_rxframe.dataByte5;
		msg->data[6]=can2_rxframe.dataByte6;
		msg->data[7]=can2_rxframe.dataByte7;
		if(can2_rxframe.dataByte0 == 1.0)
		{
			CAN_SetMode(MODE_PERIODIC);
		}
		else
		{
			CAN_SetMode(MODE_AT_START);
		}
	}
	else{
		//completar para otro CAN
	}
}

uint8_t CAN_Receive_Msg(CAN_msg *buf)
{
	uint8_t datalen=0;
	if(rxComplete==true)
	{
		rxComplete=false;
		buf->len = can2_rxframe.length;
		buf->format = kFLEXCAN_FrameFormatExtend;
		buf->id = 0;
		CAN_rdMsg(buf->id, buf);
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

void CAN_SetMode (uint8_t value)
{
	mode = value;
}

uint8_t CAN_GetMode (void)
{
	return mode;
}
