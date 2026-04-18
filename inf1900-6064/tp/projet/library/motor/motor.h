// Alex Carpentier

// Motor controls two DC motors via PWM on Timer1 and direction pins on PORTD.
// Provides speed and direction adjustment, straight movement with hardware correction,
// and timed turn maneuvers using Timer0 overflow callbacks.

#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer/timer.h"
#include "debug.h"
#include "led/led.h"

class Motor{
public:
    enum Direction{
        FORWARD,
        BACKWARD
    };

    static void init();
    static void adjustMotor(Direction dirLeft, uint8_t powerLevelLeft, Direction dirRight, uint8_t powerLevelRight);
    static void moveStraight(Direction dir, uint8_t powerLevel);
    static void turnLeft();
    static void turnRight();
    static void turn180();
    static void stop();
    static void adjustForceCorrection(int8_t force);

private:
    // a positive value for FORCE_CORRECTION will give more power to the right motor and less to the left motor
    // a negative value for FORCE_CORRECTION will give more power to the left motor and less to the right motor
    // the value is only used in the function <moveStraight>
    static int8_t forceCorrection;

    static const uint16_t TIME_TURN_FAST = 600;
    static const uint16_t TIME_TURN_SLOW = 800;

    static const uint16_t TIME_TURN_180_FAST = 1025;
    static const uint16_t TIME_TURN_180_SLOW = 1600;

    static const uint8_t TURN_SPEED_SLOW = 30;
    static const uint8_t TURN_SPEED = 180; 

    enum Side{
        LEFT,
        RIGHT
    };

    static uint8_t counter;
    static void adjustPwm(uint8_t powerLevelLeft, uint8_t powerLevelRight);
    static void manageDirection(Motor::Side side, Motor::Direction dir);
    static void activatePin(uint8_t pin);
    static void deactivatePin(uint8_t pin);
};