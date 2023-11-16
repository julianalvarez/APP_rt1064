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

typedef struct tagABGC_MSG_T
{
	uint8_t   		mode;
	uint8_t   		dato1;
	uint8_t   		dato2;
	uint8_t   		dato3;
	uint8_t   		dato4;
	uint8_t   		dato5;
	uint8_t   		dato6;
	uint8_t   		dato7;

} ABGC_MSG_T;

/* Prototypes *****************************************************************/
void 					Obj_ISR (uint8_t ctrl, CAN_msg* Msg);
void 					init_CAN (uint32_t ctrl, uint32_t baudrate);
void                    CANMSG_ABGC_Init (uint8_t primary);
uint32_t 				PAT_GEN_OnABGC (uint32_t Addr);

#endif /* FLEXCAN_MODULE_H_ */
