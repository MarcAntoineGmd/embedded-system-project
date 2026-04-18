#pragma once

#include <avr/io.h>

#define LINE_SENSOR_D1 PA3
#define LINE_SENSOR_D2 PA4
#define LINE_SENSOR_D3 PA5
#define LINE_SENSOR_D4 PA6
#define LINE_SENSOR_D5 PA7

class LineSensor {
public:
    static void init();
    static uint8_t read();
    
    static bool S1();
    static bool S2();
    static bool S3();
    static bool S4();
    static bool S5();

    static bool isOnLine();
    static bool isAtWall();
};
