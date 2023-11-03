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


uint8_t 	CAN_Send_Msg(uint8_t* msg,uint8_t len);

uint8_t 	CAN_Receive_Msg(uint8_t *buf);

void 		CAN_SetMode(uint8_t value);
uint8_t 	CAN_GetMode (void);

void 		CAN_ProcessIRQ(void);
#endif /* BSP_FLEXCAN_H_ */
