/*
 * time.c
 *
 *  Created on: 15 nov. 2023
 *      Author: PLANTIUM
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpt.h"

#define GPT_1 GPT1
#define GPT_CLOCK_FREQ (CLOCK_GetFreq(kCLOCK_PeriphClk))

static uint32_t nowTime = 0;

void TIME_Init (uint32_t TickInMicroseconds)
{
    gpt_config_t gptConfig;

    GPT_GetDefaultConfig(&gptConfig);

    /* Initialize GPT module */
    GPT_Init(GPT_1, &gptConfig);

    /* Divide GPT clock source frequency by 1 inside GPT module */
    GPT_SetClockDivider(GPT_1, 1);

    /* Set both GPT modules to 32-bit mode */
    GPT_SetOutputCompareValue(GPT_1, kGPT_OutputCompare_Channel1, CLOCK_GetFreq(kCLOCK_OscClk) / TickInMicroseconds);

    /* Enable GPT Output Compare1 interrupt */
    GPT_EnableInterrupts(GPT_1, kGPT_OutputCompare1InterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(GPT1_IRQn);

    /* Start Timer */
    GPT_StartTimer(GPT_1);
}

void GPT1_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    GPT_ClearStatusFlags(GPT_1, kGPT_OutputCompare1Flag);

    GPT_1->CNT;
    /* Add your interrupt code here */
    nowTime++;
}

uint32_t TIME_Get(void)
{
	return nowTime;
}
