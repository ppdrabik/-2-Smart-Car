#include "motor.h"

static axis_s axis;
static state_s MOTOR_Get_State();

void MOTOR_Get_Data()
{
    const rx_buffer_s *buffer = LoRa_Get_Buffer();
    axis.y = buffer->data[0];
    axis.x = buffer->data[1];
}

static state_s MOTOR_Get_State()
{
    MOTOR_Get_Data();
    state_s current_state;

    if(axis.y == 1)
	{
		current_state.y_state = DRIVE;
    }
    else if (axis.y == -1)
    {
        current_state.y_state = REVERSE;
    }
    else
    {
        current_state.y_state = IDLE;
    }

    
    if(axis.x == 1)
    {
        current_state.x_state = RIGHT;
    }
    else if (axis.x == -1)
    {
        current_state.x_state = LEFT;
    }
    else
    {
        current_state.x_state = IDLE;
    }
    
    return current_state;
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
    state_s state = MOTOR_Get_State();

    switch (state.y_state)
	{
	case IDLE:
		MOTOR_1_Idle();
		break;

	case DRIVE:
		MOTOR_1_Drive();
		break;

	case REVERSE:
		MOTOR_1_Reverse();
		break;

	default: break;
	}

	switch (state.x_state)
	{
	case IDLE:
		MOTOR_2_Idle();
		break;

	case RIGHT:
		MOTOR_2_Right();
		break;

	case LEFT:
		MOTOR_2_Left();
		break;

	default: break;
	}
}