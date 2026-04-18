#include "infraredSensor.h"
#include "can.h"

Can InfraredSensor::adc_{};

void InfraredSensor::init()
{
    adc_.init();
}

uint16_t InfraredSensor::read()
{
    return adc_.lecture(IR_SENSOR_PIN);
}

uint16_t InfraredSensor::getDistance()
{
    uint16_t adc = read();
    
    if (adc >= 700) {
        return 60;
    }
    
    if (adc < 50) {
        return 800;
    }
    
    uint16_t distance = (uint16_t)((-0.0000204089 * adc * adc - 0.00655699 * adc + 20.8986) * 10);
    
    if (distance < 50) return 50;
    if (distance > 800) return 800;
    
    return distance;
}
