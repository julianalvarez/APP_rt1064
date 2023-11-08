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

#define MODE_AT_START 0
#define MODE_PERIODIC 1

/* Enums **********************************************************************/
enum {
    CAN_NO_ERR,
    CAN_RANGE_ERR,
    CAN_BAD_BUS,
    CAN_BAD_OBJ,
    CAN_BAD_RATE,
    CAN_QUEUE_INIT_ERR,
    CAN_NO_INIT,
    CAN_NO_MSG,
    CAN_INIT_CHANGE,
    CAN_OBJ_BUSY,
    CAN_OBJ_MISMATCH,
    CAN_Q_FULL,
    CAN_Q_OVERFLOW,
    CAN_BUS_OFF,
    CAN_BUS_WARN,
	CAN_BUS_ERRBIT,
};

typedef struct
{
    uint32_t dwId;                         /** Identifier */
    uint8_t  bXtd;                         /** Laenge Bit Identifier */
    uint8_t  bDlc;                         /** Anzahl der empfangenen Daten */
    uint8_t  abData[8];                    /** Datenpuffer */
} tSend;

typedef struct tagCAN_MSG {
    uint32_t id;                    /* 29 bit identifier                    */
    uint8_t  data[8];               /* Data field                           */
    uint8_t  len;                   /* Length of data field in bytes        */
    uint8_t  format;                /* 0 - STANDARD, 1- EXTENDED IDENTIFIER */
} CAN_msg;

int32_t                 init_can (uint8_t bBusNumber,uint16_t wGlobMask, uint32_t dwGlobMask,uint32_t dwGlobMaskLastmsg, uint16_t wBitrate);
int32_t                 send_can_msg (uint8_t bBusNumber,uint8_t bMsgObj, tSend *ptSend );
uint8_t 				CAN_Receive_Msg(CAN_msg *buf);

void 					CAN_SetMode(uint8_t value);
uint8_t 				CAN_GetMode (void);


#endif /* CAN_EXT_H_ */
