#include "vl53l0x_api.h"
#include "i2c.h"

typedef struct 
{
    VL53L0X_RangingMeasurementData_t pdata;
}vl53l0x_s;


void VL53L0X_Init();
uint16_t VL53L0X_Get_Distance_IT();
const vl53l0x_s *VL53L0X_Get_Measurement_Data();