/*
 * can_ext.c
 *
 *  Created on: 7 nov. 2023
 *      Author: PLANTIUM
 */
/* Include ********************************************************************/
#include <can_ext.h>
#include <string.h>
#include "peripherals.h"

/* Functions ******************************************************************/
int32_t init_can (uint8_t bBusNumber,uint16_t wGlobMask,
								  uint32_t dwGlobMask,uint32_t dwGlobMaskLastmsg,
								  uint16_t wBitrate)
{
    if (bBusNumber >= CAN_MAX_BUS_NR) {
        return (CAN_RANGE_ERR);
    } else {
		if(bBusNumber == 0){
			BOARD_InitUART();
			BOARD_InitCAN2();
			BOARD_InitADC1();
			FLEXCAN_SetRxMbGlobalMask(BOARD_CAN2_PERIPHERAL, FLEXCAN_RX_MB_EXT_MASK(0, 0, 0));
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


