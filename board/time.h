/*
 * time.h
 *
 *  Created on: 15 nov. 2023
 *      Author: PLANTIUM
 */

#ifndef TIME_H_
#define TIME_H_


void 			        TIME_Init (uint32_t TickInMicroseconds);
void 			        TIME_Close (void);
uint32_t 		        TIME_Get(void);


#endif /* TIME_H_ */
