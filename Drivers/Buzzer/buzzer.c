#include "buzzer.h"

void BUZZER_Set_Frequency(uint32_t frequency)
{
    if (frequency > 0)
    {
        float temp_prescaler = (SystemCoreClock / (frequency * (LL_TIM_GetAutoReload(TIM_HANLDER) + 1))) - 1; 

        uint32_t prescaler = (uint32_t)temp_prescaler;
        uint32_t dutycycle = LL_TIM_GetAutoReload(TIM_HANLDER)/2;

        LL_TIM_SetPrescaler(TIM_HANLDER, prescaler);
        LL_TIM_OC_SetCompareCH1(TIM_HANLDER, dutycycle);

        LL_TIM_EnableCounter(TIM_HANLDER);
        LL_TIM_CC_EnableChannel(TIM_HANLDER, LL_TIM_CHANNEL_CH1);
    }
    else
    {
        LL_TIM_DisableCounter(TIM_HANLDER);
        LL_TIM_CC_DisableChannel(TIM_HANLDER, LL_TIM_CHANNEL_CH1);
    }
}