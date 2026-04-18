// Alex Carpentier

// Movement moves through the course and goes to selected places

#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "motor/motor.h"
#include "lineSensor/lineSensor.h"

class Movement{
public:
    // goes left by default, call this to switch to going right
    static void goRight();    

    // calls func when finished
    static void checkCorridor1();
    static void goToNextRoom();
    static void checkCorridor2(uint8_t parking);


private:
    static const uint8_t SPEED = 150;
    static const uint16_t TIME_BETWEEN_INSTRUCTIONS = 500;
    static const uint16_t TIME_MOVE_AFTER_WALL = 300;
    static bool goingRight;

    // turns toward the inside of the course
    static void turnIn();
    // turns toward the outside of the course
    static void turnOut();

    static void turnIn90();

    static void turnOut90();

    static void turn180();

    static void staticAlign();

    static void alignOnExtremeSensors();

    static void delay();

    static void goToWall();

    static void goToCorridorend();

    //returns true when at wall
    static bool adjustCorridor();
    static bool adjustSideCorridor();

    static void goToSideCorridorEnd();

    static void goToRoom1();
    
    static bool getOutsideSensor();
    static bool getMidOutsideSensor();
    static bool getMidSensor();
    static bool getMidInsideSensor();
    static bool getInsideSensor();

    static void goToNextEntrance();

    static void park(uint8_t parking);
};