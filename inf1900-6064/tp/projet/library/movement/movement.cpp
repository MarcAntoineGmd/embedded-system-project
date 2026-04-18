#include "movement.h"
#include <motor.h>

bool Movement::goingRight = false;

#pragma region corridor2

void Movement::checkCorridor2(uint8_t parking){
    goToWall();
    goToCorridorend();
    goToSideCorridorEnd();
    park(parking);
}

static const uint8_t COUNTER_FIRST_PARKING = 170;
static const uint8_t COUNTER_NEXT_PARKING = 70;
static const uint8_t TIME_BETWEEN_CHECKS_PARKING = 25;
static const uint16_t DELAY_GOING_IN_PARKING = 1300;
static const uint16_t PARKING_DISTANCE_MS = 800; // à changer selon la distance entre les places de parking et la vitesse du robot (pas pu tester avec parcours)

void Movement::park(uint8_t parking){
    turnIn();

    for(uint8_t i = 0; i < COUNTER_FIRST_PARKING; i++){
        adjustCorridor();
        Motor::moveStraight(Motor::FORWARD, SPEED);
        _delay_ms(TIME_BETWEEN_CHECKS_PARKING);
    }

    uint8_t slot = goingRight ? (5 - parking) : parking;
    
    uint16_t duration = slot * PARKING_DISTANCE_MS;
    
    Motor::moveStraight(Motor::FORWARD, SPEED);
    
    uint16_t elapsed = 0;
    static const uint16_t STEP_MS = 10;
    while(elapsed < duration){
        _delay_ms(STEP_MS);
        elapsed += STEP_MS;
    }
    
    Motor::stop();

    turnIn90();
    Motor::moveStraight(Motor::FORWARD, SPEED);

    while(!LineSensor::isAtWall());
    
    Motor::stop();
}


#pragma endregion

#pragma region NextRoom

void Movement::goToNextRoom(){
    goToWall();
    goToNextEntrance();
}


static const uint8_t COUNTER_NEXT_ROOM = 120;
static const uint8_t TIME_BETWEEN_CHECKS_NEXT_ROOM = 25;
void Movement::goToNextEntrance(){
    turnIn();

    for(uint8_t i = 0; i < COUNTER_NEXT_ROOM; i++){
        adjustCorridor();
        Motor::moveStraight(Motor::FORWARD, SPEED);
        _delay_ms(TIME_BETWEEN_CHECKS_NEXT_ROOM);
    }
    Motor::adjustForceCorrection(6);


    Motor::stop();
    turnIn90();
}

#pragma endregion

#pragma region corridor1

void Movement::checkCorridor1(){
    goToWall();
    goToCorridorend();
    goToSideCorridorEnd();
    goToRoom1();
}



static const uint8_t COUNTER_ROOM1 = 80;
static const uint8_t TIME_BETWEEN_CHECKS_ROOM1 = 25;
void Movement::goToRoom1(){
    turnIn();

    for(uint8_t i = 0; i < COUNTER_ROOM1; i++){
        adjustCorridor();
        Motor::moveStraight(Motor::FORWARD, SPEED);
        _delay_ms(TIME_BETWEEN_CHECKS_ROOM1);
    }
    Motor::adjustForceCorrection(6);

    Motor::stop();
    turnIn90();
}

#pragma endregion

#pragma region General functions

void Movement::goRight(){
    goingRight = true;
}

void Movement::delay(){
    _delay_ms(TIME_BETWEEN_INSTRUCTIONS);
}

#pragma region turns

static const uint8_t TURN_SLOW_SPEED = 130;
static const uint16_t TURN_PULSE_ON = 50;
static const uint16_t TURN_PULSE_OFF = 30;

void Movement::turnIn(){
    delay();
    while(!getOutsideSensor()){
        if(goingRight)
            Motor::adjustMotor(Motor::BACKWARD, TURN_SLOW_SPEED, Motor::FORWARD, TURN_SLOW_SPEED);
        else
            Motor::adjustMotor(Motor::FORWARD, TURN_SLOW_SPEED, Motor::BACKWARD, TURN_SLOW_SPEED);
        _delay_ms(TURN_PULSE_ON);
        Motor::stop();
        _delay_ms(TURN_PULSE_OFF);
    }
    Motor::stop();
    staticAlign();
    delay();
}

void Movement::turnOut(){
    delay();
    while(!getInsideSensor()){
        if(goingRight)
            Motor::adjustMotor(Motor::FORWARD, TURN_SLOW_SPEED, Motor::BACKWARD, TURN_SLOW_SPEED);
        else
            Motor::adjustMotor(Motor::BACKWARD, TURN_SLOW_SPEED, Motor::FORWARD, TURN_SLOW_SPEED);
        _delay_ms(TURN_PULSE_ON);
        Motor::stop();
        _delay_ms(TURN_PULSE_OFF);
    }
    Motor::stop();
    staticAlign();
    delay();
}
// turns toward the inside of the course
void Movement::turnIn90(){
    delay();
    if(goingRight)
        Motor::turnLeft();
    else
        Motor::turnRight();
    delay();
}

// turns toward the outside of the course
void Movement::turnOut90(){
    delay();
    if(goingRight)
        Motor::turnRight();
    else
        Motor::turnLeft();
    delay();
}

void Movement::turn180(){
    delay();
    Motor::turn180();
    delay();
}

static const uint16_t TILT_PULSE_ON  = 25;
static const uint16_t TILT_PULSE_OFF = 5;

void Movement::staticAlign(){
    while(getOutsideSensor()){
        if(goingRight)
            Motor::adjustMotor(Motor::BACKWARD, TURN_SLOW_SPEED, Motor::FORWARD, TURN_SLOW_SPEED);
        else
            Motor::adjustMotor(Motor::FORWARD, TURN_SLOW_SPEED, Motor::BACKWARD, TURN_SLOW_SPEED);
        _delay_ms(TILT_PULSE_ON);
        Motor::stop();
        _delay_ms(TILT_PULSE_OFF);
    }

    while(getInsideSensor()){
        if(goingRight)
            Motor::adjustMotor(Motor::FORWARD, TURN_SLOW_SPEED, Motor::BACKWARD, TURN_SLOW_SPEED);
        else
            Motor::adjustMotor(Motor::BACKWARD, TURN_SLOW_SPEED, Motor::FORWARD, TURN_SLOW_SPEED);
        _delay_ms(TILT_PULSE_ON);
        Motor::stop();
        _delay_ms(TILT_PULSE_OFF);
    }
}

void Movement::alignOnExtremeSensors(){
    while(getOutsideSensor()){
        if(goingRight)
            Motor::adjustMotor(Motor::BACKWARD, TURN_SLOW_SPEED, Motor::FORWARD, TURN_SLOW_SPEED);
        else
            Motor::adjustMotor(Motor::FORWARD, TURN_SLOW_SPEED, Motor::BACKWARD, TURN_SLOW_SPEED);
        _delay_ms(TILT_PULSE_ON);
        Motor::stop();
        _delay_ms(TILT_PULSE_OFF);
    }
    while(getInsideSensor()){
        if(goingRight)
            Motor::adjustMotor(Motor::FORWARD, TURN_SLOW_SPEED, Motor::BACKWARD, TURN_SLOW_SPEED);
        else
            Motor::adjustMotor(Motor::BACKWARD, TURN_SLOW_SPEED, Motor::FORWARD, TURN_SLOW_SPEED);
        _delay_ms(TILT_PULSE_ON);
        Motor::stop();
        _delay_ms(TILT_PULSE_OFF);
    }
}

#pragma endregion

#pragma region sensors

bool Movement::getOutsideSensor(){
    if(goingRight)
        return LineSensor::S5();
    return LineSensor::S1();
}

bool Movement::getMidOutsideSensor(){
    if(goingRight)
        return LineSensor::S4();
    return LineSensor::S2();
}

bool Movement::getMidSensor(){
    return LineSensor::S3();
}

bool Movement::getMidInsideSensor(){
    if(goingRight)
        return LineSensor::S2();
    return LineSensor::S4();
}

bool Movement::getInsideSensor(){
    if(goingRight)
        return LineSensor::S1();
    return LineSensor::S5();
}

#pragma endregion

#pragma region corridors

static const uint8_t ADJUST_NO_LINE = 6;
static const int8_t ADJUST_SMALL = -20;
static const int8_t ADJUST_BIG = -25;
// return true if at corridor end
bool Movement::adjustCorridor(){
    int8_t force = ADJUST_NO_LINE;

    if(getOutsideSensor())
        force = ADJUST_SMALL;

    if(getInsideSensor())
        force = -1.5 * ADJUST_SMALL;

    if(getMidOutsideSensor())
        force = ADJUST_BIG;

    if (getMidInsideSensor())
        force = -1.5 * ADJUST_BIG;

    if(goingRight)
        force *= -1;

    Motor::adjustForceCorrection(force);

    return LineSensor::isAtWall();
}

bool Movement::adjustSideCorridor(){
    int8_t force = ADJUST_NO_LINE;

    if(getOutsideSensor())
        force = ADJUST_SMALL;
    
    if(getInsideSensor())
        force = -1.5 * ADJUST_SMALL;

    if(goingRight)
        force *= -1;

    Motor::adjustForceCorrection(force);

    return LineSensor::isAtWall();
}

static const uint16_t TIME_REVERSE_BEFORE_TURN = 1500;

// does a 180 and goes straight until wall
void Movement::goToWall() {
    turn180();

    Motor::moveStraight(Motor::FORWARD, SPEED);

    while(!LineSensor::isAtWall());

    _delay_ms(TIME_MOVE_AFTER_WALL);
    Motor::stop();
}

// void Movement::goToCorridorend(){
//     turnIn();

//     while(!adjustCorridor()){
//          Motor::moveStraight(Motor::FORWARD, SPEED);
//     }

//     Motor::adjustForceCorrection(6);
//     _delay_ms(TIME_MOVE_AFTER_WALL);
//     Motor::stop();
// }

// void Movement::goToSideCorridorEnd(){
//     turnIn();

//     while(!adjustSideCorridor()){
//          Motor::moveStraight(Motor::FORWARD, SPEED);
//          // mettre ici la fonction pour check le tape dans le corridor
//     }

    
//     Motor::adjustForceCorrection(6);
//     _delay_ms(TIME_MOVE_AFTER_WALL);
//     Motor::stop();
// }

void Movement::goToCorridorend(){
    turnIn();

    while(!adjustCorridor()){
        if(getOutsideSensor() || getInsideSensor()){
            Motor::stop();
            _delay_ms(500);
            alignOnExtremeSensors();
            Motor::moveStraight(Motor::FORWARD, SPEED);
            _delay_ms(500);
        } else {
            Motor::moveStraight(Motor::FORWARD, SPEED);
        }
    }

    Motor::adjustForceCorrection(6);
    _delay_ms(TIME_MOVE_AFTER_WALL);
    Motor::stop();
}

void Movement::goToSideCorridorEnd(){
    turnIn();

    while(!adjustSideCorridor()){
        if(getOutsideSensor() || getInsideSensor()){
            Motor::stop();
            _delay_ms(500);
            alignOnExtremeSensors();
            Motor::moveStraight(Motor::FORWARD, SPEED);
            _delay_ms(500);
        } else {
            Motor::moveStraight(Motor::FORWARD, SPEED);
        }
    }

    Motor::adjustForceCorrection(6);
    _delay_ms(TIME_MOVE_AFTER_WALL);
    Motor::stop();
}

#pragma endregion

#pragma endregion