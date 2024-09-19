#include "rgb.h"

/* Every bit of RGB is changed to byte of PWM duty cycle that */
/* represent eather high or low singal */

static led_data_s led_data;
static void RGB_Bits_To_Byte(int rgb);

static void RGB_Bits_To_Byte(int rgb)
{
	led_data.rgb_to_send[25] = 0;
	for(uint8_t i = 0; i < 24; i++)
	{
		if((rgb >> i) & 0x01)
		{
			led_data.rgb_to_send[i] = LED_HIGH_SIGNAL_PWM;
		}
		else
		{
			led_data.rgb_to_send[i] = LED_LOW_SIGNAL_PWM;
		}
	}
}

void RGB_Set_Color(uint8_t r, uint8_t g, uint8_t b)
{
	int rgb =(g | r << 8 | b << 16);
	RGB_Bits_To_Byte(rgb);

	LL_TIM_EnableIT_UPDATE(TIM_HANDLER);
	LL_TIM_EnableDMAReq_UPDATE(TIM_HANDLER);
	LL_DMAMUX_SetRequestID(DMAMUX1, LL_DMAMUX_CHANNEL_0, LL_DMAMUX_REQ_TIM3_UP);
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&led_data.rgb_to_send, (uint32_t)&TIM3->CCR1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 25);
	LL_TIM_CC_EnableChannel(TIM_HANDLER,LL_TIM_CHANNEL_CH1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_TIM_EnableCounter(TIM_HANDLER);
}

