#ifndef SRC_BUZZER_H_
#define SRC_BUZZER_H_

#include <stdint.h>
#include <main.h>

#define TIM_HANLDER TIM4

void BUZZER_Set_Frequency(uint32_t frequency);
void BUZZER_On();
void BUZZER_Off();
void BUZZER_Toggle();

#endif