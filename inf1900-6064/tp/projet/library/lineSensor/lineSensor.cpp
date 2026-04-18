#include "lineSensor.h"

void LineSensor::init()
{
    DDRA &= ~((1 << LINE_SENSOR_D1) | (1 << LINE_SENSOR_D2) | (1 << LINE_SENSOR_D3) | 
               (1 << LINE_SENSOR_D4) | (1 << LINE_SENSOR_D5));
}

uint8_t LineSensor::read()
{
    return PINA & ((1 << LINE_SENSOR_D1) | (1 << LINE_SENSOR_D2) | (1 << LINE_SENSOR_D3) | 
                   (1 << LINE_SENSOR_D4) | (1 << LINE_SENSOR_D5));
}

bool LineSensor::S1()
{
    return PINA & (1 << LINE_SENSOR_D1);
}

bool LineSensor::S2()
{
    return PINA & (1 << LINE_SENSOR_D2);
}

bool LineSensor::S3()
{
    return PINA & (1 << LINE_SENSOR_D3);
}

bool LineSensor::S4()
{
    return PINA & (1 << LINE_SENSOR_D4);
}

bool LineSensor::S5()
{
    return PINA & (1 << LINE_SENSOR_D5);
}

bool LineSensor::isOnLine()
{
    return read();
}

static const uint8_t BIT_MASK_WALL = (1 << LINE_SENSOR_D1) | (1 << LINE_SENSOR_D2) | (1 << LINE_SENSOR_D3) | 
                   (1 << LINE_SENSOR_D4) | (1 << LINE_SENSOR_D5);
bool LineSensor::isAtWall()
{
    return read() == BIT_MASK_WALL;
}