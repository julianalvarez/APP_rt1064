/*
 * can_ext.h
 *
 *  Created on: 7 nov. 2023
 *      Author: PLANTIUM
 */

#ifndef CAN_EXT_H_
#define CAN_EXT_H_

#include <stdint.h>
#include "board.h"
#include <can.h>

typedef struct
{
    uint32_t dwId;                         /** Identifier */
    uint8_t  bXtd;                         /** Laenge Bit Identifier */
    uint8_t  bDlc;                         /** Anzahl der empfangenen Daten */
    uint8_t  abData[8];                    /** Datenpuffer */
} tSend;


int32_t                 init_can (uint8_t bBusNumber,uint16_t wGlobMask, uint32_t dwGlobMask,uint32_t dwGlobMaskLastmsg, uint16_t wBitrate);
int32_t                 send_can_msg (uint8_t bBusNumber,uint8_t bMsgObj, tSend *ptSend );


#endif /* CAN_EXT_H_ */
