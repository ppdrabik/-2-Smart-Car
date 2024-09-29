#include "motor.h"

static motor_t motor;

static void MOTOR_Set_State();
static void MOTOR_Get_Data();

static void MOTOR_Get_Data()
{
    const rx_buffer_s *buffer = LoRa_Get_Buffer();
    motor.axis_value.y = buffer->data[0];
    motor.axis_value.x = buffer->data[1];
}

static void MOTOR_Set_State()
{
    MOTOR_Get_Data();

    if (motor.axis_value.y == 1)
    {
        motor.state_value.y_state = DRIVE;
    }
    else if (motor.axis_value.y == -1)
    {
        motor.state_value.y_state = REVERSE;
    }
    else
    {
        motor.state_value.y_state = IDLE;
    }

    if (motor.axis_value.x == 1)
    {
        motor.state_value.x_state = RIGHT;
    }
    else if (motor.axis_value.x == -1)
    {
        motor.state_value.x_state = LEFT;
    }
    else
    {
        motor.state_value.x_state = IDLE;
    }
}

void MOTOR_1_Drive()
{
    LL_GPIO_SetOutputPin(GPIOA, IN_1_Pin);
    LL_GPIO_ResetOutputPin(GPIOA, IN_2_Pin);
    LL_TIM_OC_SetCompareCH1(TIM2, PWM_1_DUTY_CYCLE);
}

void MOTOR_1_Reverse()
{
    LL_GPIO_ResetOutputPin(GPIOA, IN_1_Pin);
    LL_GPIO_SetOutputPin(GPIOA, IN_2_Pin);
    LL_TIM_OC_SetCompareCH1(TIM2, PWM_1_DUTY_CYCLE);
}

void MOTOR_2_Right()
{
    LL_GPIO_SetOutputPin(GPIOB, IN_3_Pin);
    LL_GPIO_ResetOutputPin(GPIOB, IN_4_Pin);
    LL_TIM_OC_SetCompareCH2(TIM2, PWM_2_DUTY_CYCLE);
}

void MOTOR_2_Left()
{
    LL_GPIO_ResetOutputPin(GPIOB, IN_3_Pin);
    LL_GPIO_SetOutputPin(GPIOB, IN_4_Pin);
    LL_TIM_OC_SetCompareCH2(TIM2, PWM_2_DUTY_CYCLE);
}

void MOTOR_1_Idle()
{
    LL_TIM_OC_SetCompareCH1(TIM2, PWM_IDLE_DUTY_CYCLE);
}

void MOTOR_2_Idle()
{
    LL_TIM_OC_SetCompareCH2(TIM2, PWM_IDLE_DUTY_CYCLE);
}

void MOTOR_Set_Direction()
{
    MOTOR_Set_State();

    switch (motor.state_value.y_state)
    {
    case IDLE:
        MOTOR_1_Idle();
        printf("IDLE:%lu \n\r", TIM2->CCR1);
        break;

    case DRIVE:
        MOTOR_1_Drive();
        printf("DRIVE:%lu \n\r", TIM2->CCR1);
        break;

    case REVERSE:
        MOTOR_1_Reverse();
        printf("REVERSE:%lu \n\r", TIM2->CCR1);
        break;

    default:
        break;
    }

    switch (motor.state_value.x_state)
    {
    case IDLE:
        MOTOR_2_Idle();
        printf("IDLE:%lu \n\r", TIM2->CCR2);
        break;

    case RIGHT:
        MOTOR_2_Right();
        printf("RIGHT:%lu \n\r", TIM2->CCR2);
        break;

    case LEFT:
        MOTOR_2_Left();
        printf("LEFT:%lu \n\r", TIM2->CCR2);
        break;

    default:
        break;
    }
}

const motor_t *MOTOR_Get_Struct_Data(void)
{
    return &motor;
}
