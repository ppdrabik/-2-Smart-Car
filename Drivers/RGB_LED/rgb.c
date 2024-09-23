#include "rgb.h"


static led_data_s led_data;


static void RGB_Bits_To_Byte(uint32_t rgb);

static void RGB_Bits_To_Byte(uint32_t rgb)
{
	for (uint8_t i = 0; i < 24; i++)
	{
		if ((rgb >> i) & 0x01)
		{
			led_data.rgb_to_send[i] = LED_HIGH_SIGNAL_PWM;
		}
		else
		{
			led_data.rgb_to_send[i] = LED_LOW_SIGNAL_PWM;
		}
	}
}


void RGB_Init(void)
{
	uint32_t rgb = 0;
	RGB_Bits_To_Byte(rgb);

	led_data.rgb_to_send[24] = 0;
	led_data.rgb_to_send[25] = 0;

	LL_TIM_EnableIT_UPDATE(TIM_HANDLER);
	LL_TIM_EnableDMAReq_UPDATE(TIM_HANDLER);
	LL_DMAMUX_SetRequestID(DMAMUX1, LL_DMAMUX_CHANNEL_0, LL_DMAMUX_REQ_TIM3_UP);
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);

	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&led_data.rgb_to_send, (uint32_t)&TIM3->CCR1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 26);

	LL_TIM_CC_EnableChannel(TIM_HANDLER,LL_TIM_CHANNEL_CH1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_TIM_EnableCounter(TIM_HANDLER);

	RGB_Set_DMA_Busy_Flag();
	RGB_Reset();
}


led_status_e RGB_Set_Color(uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t rgb = (g | r << 8 | b << 16);
	led_data.current_r = r;
	led_data.current_g = g;
	led_data.current_b = b;

	while (led_data.dma_bussy_flag == true) {};


	RGB_Bits_To_Byte(rgb);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&led_data.rgb_to_send, (uint32_t)&TIM3->CCR1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 26);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	
	LL_TIM_EnableCounter(TIM_HANDLER);
	RGB_Set_DMA_Busy_Flag();
	RGB_Reset();

	led_data.current_status = LED_ON;
	return LED_ON;
}

void RGB_Reset()
{	
	while (led_data.dma_bussy_flag == true) {};

	for (uint8_t i = 0; i < 50; i++)
	{
		led_data.reset_signal[i] = 0;
	}

	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&led_data.reset_signal, (uint32_t)&TIM3->CCR1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 50);

	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_TIM_EnableCounter(TIM_HANDLER);

	RGB_Set_DMA_Busy_Flag();

}

void RGB_Turn_On()
{
	RGB_Set_Color(led_data.current_r, led_data.current_g, led_data.current_b);
}


led_status_e RGB_Turn_Off()
{
	uint32_t rgb = 0;

	while (led_data.dma_bussy_flag == true) {};

	RGB_Bits_To_Byte(rgb);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&led_data.rgb_to_send, (uint32_t)&TIM3->CCR1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 26);

	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_TIM_EnableCounter(TIM_HANDLER);

	RGB_Set_DMA_Busy_Flag();
	RGB_Reset();

	led_data.current_status = LED_OFF;
	return LED_OFF;
}


void RGB_Toggle()
{
	if (led_data.current_status == LED_ON)
	{
		RGB_Turn_Off();
	}
	else
	{
		RGB_Turn_On();
	}
}

void RGB_Set_DMA_Busy_Flag()
{
	led_data.dma_bussy_flag = true;
}

void RGB_Reset_DMA_Busy_Flag()
{
	led_data.dma_bussy_flag = false;
}

const bool *RGB_Get_DMA_Bussy_Flag()
{
	return &led_data.dma_bussy_flag;
}

