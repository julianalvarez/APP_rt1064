/*
 * can.c
 *
 *  Created on: 9 nov. 2023
 *      Author: PLANTIUM
 */

#include <can.h>
#include "FlexCAN_Module.h"

flexcan_frame_t can2_rxframe;
volatile bool rxComplete = false;

static CAN_msg          CAN_RxMsg[CAN_MAX_BUS_NR]; /* CAN message for receiving */

void CAN_ProcessIRQ(void);


void CAN_wrMsg (uint32_t ctrl, CAN_msg *msg)
{
	flexcan_frame_t frame;

	frame.format = msg->format;
	frame.type = kFLEXCAN_FrameTypeData;
	frame.id = FLEXCAN_ID_EXT(msg->id);
	frame.length = msg->len;

	frame.dataByte0 = msg->data[0];
	frame.dataByte1 = msg->data[1];
	frame.dataByte2 = msg->data[2];
	frame.dataByte3 = msg->data[3];
	frame.dataByte4 = msg->data[4];
	frame.dataByte5 = msg->data[5];
	frame.dataByte6 = msg->data[6];
	frame.dataByte7 = msg->data[7];

	if(ctrl == 0)
	{
		FLEXCAN_TransferSendBlocking(TS_CAN, TX_MESSAGE_BUFFER_NUM, &frame);
	}
	else{
	}

}

void CAN_rdMsg (uint32_t ctrl, CAN_msg *msg)
{
    /* Read frame informations */
    msg->format = kFLEXCAN_FrameFormatExtend;
    msg->len    = 8;

    /* Read CAN message identifier */
    msg->id = can2_rxframe.id;

    /* DATA FRAME */
    *(uint32_t*) &msg->data[0] = can2_rxframe.dataByte0;
    *(uint32_t*) &msg->data[1] = can2_rxframe.dataByte1;
    *(uint32_t*) &msg->data[2] = can2_rxframe.dataByte2;
    *(uint32_t*) &msg->data[3] = can2_rxframe.dataByte3;
    *(uint32_t*) &msg->data[4] = can2_rxframe.dataByte4;
    *(uint32_t*) &msg->data[5] = can2_rxframe.dataByte5;
    *(uint32_t*) &msg->data[6] = can2_rxframe.dataByte6;
    *(uint32_t*) &msg->data[7] = can2_rxframe.dataByte7;

}

void CAN_ProcessIRQ(void)
{
	if (FLEXCAN_GetMbStatusFlags(TS_CAN,1<<RX_MESSAGE_BUFFER_NUM))
	{
		FLEXCAN_ClearMbStatusFlags(CAN2,1<<RX_MESSAGE_BUFFER_NUM);
		FLEXCAN_ReadRxMb(TS_CAN,RX_MESSAGE_BUFFER_NUM,&can2_rxframe);

		CAN_rdMsg(0, &CAN_RxMsg[0]);
	    //CAN_CIR_BUF_PUSH (can_RX[0], CAN_RxMsg[0]);
	    Obj_ISR (0, &CAN_RxMsg[0]);
		/*
		if(can2_rxframee.id == FLEXCAN_RX_MB_EXT_MASK(0x18FFF680, 0, 0))
		{
			rxCompletee=true;
		}*/
	}
	__DSB();
}

void BOARD_CAN2_FLEXCAN_IRQHANDLER(void)
{
	CAN_ProcessIRQ();
}
