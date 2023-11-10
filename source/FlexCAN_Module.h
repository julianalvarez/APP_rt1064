/*
 * FlexCAN_Module.h
 *
 *  Created on: 9 nov. 2023
 *      Author: PLANTIUM
 */

#ifndef FLEXCAN_MODULE_H_
#define FLEXCAN_MODULE_H_

/* Defines ********************************************************************/
#define MODE_AT_START 0
#define MODE_PERIODIC 1

/* Prototypes *****************************************************************/
void Obj_ISR (uint8_t ctrl, CAN_msg* Msg);

#endif /* FLEXCAN_MODULE_H_ */
