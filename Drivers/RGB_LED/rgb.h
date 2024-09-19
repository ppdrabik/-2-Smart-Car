#include "main.h"

#define LED_HIGH_SIGNAL_PWM		(uint8_t)7
#define LED_LOW_SIGNAL_PWM		(uint8_t)3
#define LED_RESET_SIGNAL_PWM	(uint8_t)0
#define TIM_HANDLER             TIM3

typedef struct
{
	uint8_t rgb_to_send[25];
}led_data_s;


void RGB_Set_Color(uint8_t r, uint8_t g, uint8_t b);