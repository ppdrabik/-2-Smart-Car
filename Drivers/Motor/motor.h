#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_

#include <stdint.h>
#include <lora.h>

#define PWM_1_DUTY_CYCLE 70
#define PWM_2_DUTY_CYCLE 50
#define PWM_IDLE_DUTY_CYCLE 0

typedef enum
{
	IDLE,
	DRIVE,
	REVERSE,
	RIGHT,
	LEFT,

} state_e;

typedef struct
{
	int8_t x;
	int8_t y;
} axis_s;

typedef struct
{
	state_e y_state;
	state_e x_state;
} state_s;

typedef struct motor
{
	axis_s axis_value;
	state_s state_value;
} motor_t;

void MOTOR_Set_Direction();
const motor_t *MOTOR_Get_Struct_Data(void);
void MOTOR_Drive();
void MOTOR_Reverse();
void MOTOR_Right();
void MOTOR_Left();
void MOTOR_Idle();

#endif