#include "vl53l0x.h"

static VL53L0X_Dev_t dev_objt;
static VL53L0X_DEV dev = &dev_objt;
static vl53l0x_s vl53l0x;


void VL53L0X_Init()
{
    dev->I2cHandle = &hi2c1;
    dev->I2cDevAddr = 0x52;

    VL53L0X_WaitDeviceBooted(dev);
    VL53L0X_DataInit(dev);
    VL53L0X_StaticInit(dev);
    VL53L0X_PerformRefCalibration(dev, NULL, NULL);
    VL53L0X_PerformRefSpadManagement(dev, NULL, NULL);
    VL53L0X_SetMeasurementTimingBudgetMicroSeconds(dev, 50000);
    VL53L0X_SetDeviceMode(dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
    VL53L0X_SetGpioConfig(
        dev, 
        0, 
        VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, 
        VL53L0X_GPIOFUNCTIONALITY_NEW_MEASURE_READY, 
        VL53L0X_INTERRUPTPOLARITY_HIGH
        );

    VL53L0X_ClearInterruptMask(dev, -1); 
    VL53L0X_SetDeviceMode(dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
    VL53L0X_StartMeasurement(dev);

    NVIC_EnableIRQ(EXTI3_IRQn);
}


uint16_t VL53L0X_Get_Distance_IT()
{   
    VL53L0X_ClearInterruptMask(dev, -1);
    VL53L0X_Error Status = VL53L0X_GetRangingMeasurementData(dev, &vl53l0x.pdata);
    if (Status == VL53L0X_ERROR_NONE)
    {
        return vl53l0x.pdata.RangeMilliMeter;
    }
    else
    {
        return 0;
    }
}

const vl53l0x_s *VL53L0X_Get_Measurement_Data()
{
    return &vl53l0x;
}