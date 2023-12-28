/*
 * adc.c
 *
 *  Created on: 15 dic. 2023
 *      Author: PLANTIUM
 */
/* Include ************************/
#include <adc.h>

void Init_ADC  (uint32_t ctrl, uint32_t Channel)
{
	if(ctrl == 1) //Init Pin ADC1
	{
		switch(Channel)
		{
		case 0:
			BOARD_InitPins_ADC1_ch0();
			break;
		case 9:
			BOARD_InitPins_ADC1_ch9();
			break;
		default:
			break;
		}


	}else{ //Init Pin ADC2

	}
}

void ADC_Start (uint32_t ctrl)
{
	if(ctrl == 1) //Init ADC1
	{
		BOARD_InitADC1();
	}else{ //Init ADC2

	}
}

double ADC_Get (uint32_t ctrl, uint32_t Channel)
{
	double valueADC_V;

	if(ctrl == 1) //ADC1
	{
		switch(Channel)
		{
		case 0:
			ADC_SetChannelConfig(BOARD_ADC1_PERIPHERAL, BOARD_ADC1_CH0_CONTROL_GROUP, &BOARD_ADC1_channels_config[0]);
			valueADC_V = ADC_GetChannelConversionValue(BOARD_ADC1_PERIPHERAL, 0U)* 3.3 / 4095;
			break;
		case 9:
			ADC_SetChannelConfig(BOARD_ADC1_PERIPHERAL, BOARD_ADC1_CH0_CONTROL_GROUP, &BOARD_ADC1_channels_config[1]);
			valueADC_V = ADC_GetChannelConversionValue(BOARD_ADC1_PERIPHERAL, 0U)* 3.3 / 4095;
			break;
		default:
			break;
		}

	}else{ //ADC2

	}
	return valueADC_V;
}
