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

#include "app_freertos.h"


TaskHandle_t xLORA_Rx_Task_Handler = NULL;
TaskHandle_t xReversing_Task_Handler = NULL;


void MX_FREERTOS_Init(void) 
{
    xTaskCreate(vLORA_Rx_Task, "LORA_Recieve_Task", 200, NULL, 4, &xLORA_Rx_Task_Handler);
    xTaskCreate(vReversing_Task, "Reversing", 200, NULL, 3, &xReversing_Task_Handler);

}


void vLORA_Rx_Task(void *pvParameters)
{
    uint32_t ulNotify_Value;
    const motor_t *motor_date;

    for(;;)
    {
        ulNotify_Value = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if(ulNotify_Value > 0)
        {
            LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
            LoRa_It_Rx_Callback();
            MOTOR_Set_Direction();
            motor_date = MOTOR_Get_Struct_Data();
            printf("Lora Data Reievied \n\r");
            if (motor_date->state_value.y_state == REVERSE)
            {
                NVIC_EnableIRQ(EXTI3_IRQn);
                printf("Reversing... \n\r");
            }
            else
            {
                NVIC_DisableIRQ(EXTI3_IRQn);
            } 
        }
    }
}


void vReversing_Task(void *pvParameters)
{
    uint32_t ulEvent;
    uint16_t distance;

    for(;;)
    {
        ulEvent = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if (ulEvent > 0)
        {
            distance = VL53L0X_Get_Distance_IT();
            if (distance < 15)
            {
                BUZZER_Toggle();
                printf("Distance <15 \n\r");
            }
            if (distance < 5)
            {
                BUZZER_On();
                printf("Distance <5 \n\r");
            }
        }
        
    }
}

