/*
 * FlexCAN_Module.h
 *
 *  Created on: 9 nov. 2023
 *      Author: PLANTIUM
 */

#ifndef FLEXCAN_MODULE_H_
#define FLEXCAN_MODULE_H_


#define MODE_AT_START 0
#define MODE_PERIODIC 1

void Obj_ISR (uint8_t ctrl, CAN_msg* Msg);
void 					CAN_SetMode(uint8_t value);
uint8_t 				CAN_GetMode (void);

#endif /* FLEXCAN_MODULE_H_ */
