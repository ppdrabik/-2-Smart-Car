#include "motor.h"

static axis_s axis;

void MOTOR_Get_Data()
{
    const rx_buffer_s *buffer = LoRa_Get_Buffer();
    axis.y = buffer->data[0];
    axis.x = buffer->data[1];
}