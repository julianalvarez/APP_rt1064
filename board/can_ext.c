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


void CAN_readMsg (uint32_t ctrl, CAN_msg *msg);

int32_t init_can (uint8_t bBusNumber,uint16_t wGlobMask,
								  uint32_t dwGlobMask,uint32_t dwGlobMaskLastmsg,
								  uint16_t wBitrate)
{
    if (bBusNumber >= CAN_MAX_BUS_NR) {
        return (CAN_RANGE_ERR);
    } else {
		if(bBusNumber == 0){
			BOARD_InitPinsFlexCAN();
			BOARD_InitFLEXCAN(wBitrate);
		}
		else{
			//completar para otro periferico CAN
		}
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


