#include "main.h"
#include "stdbool.h"

#define LED_HIGH_SIGNAL_PWM		(uint8_t)7
#define LED_LOW_SIGNAL_PWM		(uint8_t)3
#define LED_RESET_SIGNAL_PWM	(uint8_t)0
#define TIM_HANDLER             TIM3

typedef enum
{
	LED_OFF = 0,
	LED_ON = 1
}led_status_e;


typedef struct
{
	uint8_t rgb_to_send[26];
	uint8_t reset_signal[50];
	uint8_t current_r;
	uint8_t current_g;
	uint8_t current_b;
	led_status_e current_status;
	bool dma_bussy_flag;
}led_data_s;


void RGB_Init(void);
led_status_e RGB_Set_Color(uint8_t r, uint8_t g, uint8_t b);
void RGB_Turn_On();
led_status_e RGB_Turn_Off();
void RGB_Reset();
void RGB_Toggle();
void RGB_Set_DMA_Busy_Flag();
void RGB_Reset_DMA_Busy_Flag();
const bool *RGB_Get_DMA_Bussy_Flag();
