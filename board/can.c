/*
 * can.c
 *
 *  Created on: 9 nov. 2023
 *      Author: PLANTIUM
 */

#include <can.h>

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
