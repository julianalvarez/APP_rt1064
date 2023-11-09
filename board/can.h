/*
 * can.h
 *
 *  Created on: 9 nov. 2023
 *      Author: PLANTIUM
 */
#include <stdint.h>
#include "peripherals.h"


#ifndef CAN_H_
#define CAN_H_

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

/* Defines ********************************************************************/
#define CAN_MAX_BUS_NR                      3U

#define TX_MESSAGE_BUFFER_NUM (2)
#define RX_MESSAGE_BUFFER_NUM (1)
#define TS_CAN CAN2

typedef struct tagCAN_MSG {
    uint32_t id;                    /* 29 bit identifier                    */
    uint8_t  data[8];               /* Data field                           */
    uint8_t  len;                   /* Length of data field in bytes        */
    uint8_t  format;                /* 0 - STANDARD, 1- EXTENDED IDENTIFIER */
} CAN_msg;


void                    CAN_wrMsg (uint32_t ctrl, CAN_msg *msg);
void                    CAN_rdMsg (uint32_t ctrl, CAN_msg *msg);


#endif /* CAN_H_ */
