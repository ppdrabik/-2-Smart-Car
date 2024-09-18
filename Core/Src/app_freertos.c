/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


void BlinkTask(void * pvParameters);
void StartDefaultTask(void const * argument);
void MX_FREERTOS_Init(void);

TaskHandle_t xBlinkTaskHandle = NULL;


void MX_FREERTOS_Init(void) 
{
    xTaskCreate(BlinkTask, "BlinkTask", 100, NULL, 0, &xBlinkTaskHandle);
}


void BlinkTask(void * pvParameters)
{
    const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
    for(;;)
    {
        vTaskDelay(xDelay);
        if (!(LL_GPIO_IsOutputPinSet(GPIOA, LL_GPIO_PIN_5)))
        {
            LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);
        }
        printf("Test \n\r");
    }
}


