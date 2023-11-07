/*
 * bsp_flexcan.h
 *
 *  Created on: 31 oct. 2023
 *      Author: PLANTIUM
 */
#include <stdint.h>
#include "fsl_common.h"
#include "fsl_flexcan.h"
#include "fsl_clock.h"

#ifndef BSP_FLEXCAN_H_
#define BSP_FLEXCAN_H_

#define MODE_AT_START 0
#define MODE_PERIODIC 1


/* Typedefs *******************************************************************/
typedef struct tagCAN_MSG {
    uint32_t id;                    /* 29 bit identifier                    */
    uint8_t  data[8];               /* Data field                           */
    uint8_t  len;                   /* Length of data field in bytes        */
    uint8_t  format;                /* 0 - STANDARD, 1- EXTENDED IDENTIFIER */
} CAN_msg;

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

void 		CAN_wrMsg (uint32_t ctrl, CAN_msg *msg);







uint8_t 	CAN_Send_Msg(uint8_t* msg,uint8_t len);

uint8_t 	CAN_Receive_Msg(uint8_t *buf);

void 		CAN_SetMode(uint8_t value);
uint8_t 	CAN_GetMode (void);

void 		CAN_ProcessIRQ(void);
#endif /* BSP_FLEXCAN_H_ */
