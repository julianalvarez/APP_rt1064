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

uint8_t 	CAN2_Send_Msg(uint8_t* msg,uint8_t len);

uint8_t 	CAN2_Receive_Msg(uint8_t *buf);

void 		BSP_FLEXCAN_ProcessIRQ(void);
#endif /* BSP_FLEXCAN_H_ */
