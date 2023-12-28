/*
 * adc.h
 *
 *  Created on: 15 dic. 2023
 *      Author: PLANTIUM
 */

/* Include ********************************************************************/
#include <stdint.h>
#include "peripherals.h"
#include "board.h"
#include "pin_mux.h"

#ifndef ADC_H_
#define ADC_H_

/* Typedefs *******************************************************************/

#include <adc.h>

void Init_ADC  (uint32_t ctrl, uint32_t Channel);

void ADC_Start (uint32_t ctrl);

double ADC_Get (uint32_t ctrl, uint32_t Channel);

#endif /* ADC_H_ */
