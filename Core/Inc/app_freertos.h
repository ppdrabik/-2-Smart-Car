#ifndef SRC_APP_FREERTOS_H_
#define SRC_APP_FREERTOS_H_


#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "lora.h"
#include "motor.h"
#include "buzzer.h"
#include "vl53l0x.h"

void MX_FREERTOS_Init(void);
void vLORA_Rx_Task(void *pvParameters);
void vReversing_Task(void *pvParameters);

extern TaskHandle_t xLORA_Rx_Task_Handler;
extern TaskHandle_t xReversing_Task_Handler;

#endif