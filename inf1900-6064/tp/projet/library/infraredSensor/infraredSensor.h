#pragma once

#include <stdint.h>
#include "analogToBinary/can.h"

// GP2Y0A21YK - Sharp Infrared Distance Sensor

#define IR_SENSOR_PIN PA2  

class InfraredSensor {
public:
    static void init();
    static uint16_t read();        
    static uint16_t getDistance(); 

private:
    static Can adc_;
};
