#include "motor.h"


const uint8_t DIRECTION_PIN_LEFT = (1 << 6);
const uint8_t DIRECTION_PIN_RIGHT = (1 << 7);
const uint8_t PWM_PIN_LEFT = (1 << 4);
const uint8_t PWM_PIN_RIGHT = (1 << 5);
const uint8_t USED_PIN_PORT_D =  PWM_PIN_LEFT | PWM_PIN_RIGHT;
const uint8_t USED_PIN_PORT_C = DIRECTION_PIN_LEFT | DIRECTION_PIN_RIGHT;
const uint8_t ALL_PINS = 0xFF;
const uint8_t TIMER_TOP = 0xFF;
const uint8_t MAX_SPEED = 0xFF;
uint8_t Motor::counter = 0;
int8_t Motor::forceCorrection = 0;

void Motor::init()
{
    DDRD |= USED_PIN_PORT_D;
    DDRC |= USED_PIN_PORT_C;

    cli();
    TCCR1A = (1 << COM1A1 | 1 << COM1A0 | 1 << COM1B1 | 1 << COM1B0 | 1 << WGM10);
    TCCR1B = (1 << CS11);
    TCCR1C = 0;
    sei();

    // close the motor because the timer config turned it on automatically
    moveStraight(Motor::FORWARD, 0);
}

void Motor::activatePin(uint8_t pin){
    PORTC |= pin;
}

void Motor::deactivatePin(uint8_t pin){
    PORTC &= (ALL_PINS - pin);
}


void Motor::manageDirection(Motor::Side side, Motor::Direction dir){
    uint8_t pin = DIRECTION_PIN_RIGHT;
    if (side == Motor::Side::LEFT)
        pin = DIRECTION_PIN_LEFT;

    if(dir == Motor::Direction::FORWARD){
        deactivatePin(pin);
    }
    else{
        activatePin(pin);
    }
}

// powerLevel : [0, 255]
void Motor::adjustPwm(uint8_t powerLevelLeft, uint8_t powerLevelRight)
{
    uint8_t clockInterruptionHeightLeft = TIMER_TOP;
    if (powerLevelLeft != 0)
        clockInterruptionHeightLeft = TIMER_TOP - powerLevelLeft;

    uint8_t clockInterruptionHeightRight = TIMER_TOP;
    if (powerLevelRight != 0)
        clockInterruptionHeightRight = TIMER_TOP - powerLevelRight;

    cli();
    OCR1A = clockInterruptionHeightRight; // OCR1A controls the left wheel
    OCR1B = clockInterruptionHeightLeft; // OCR1B controls the right wheel
    sei();
}


// powerLevel : [0, 255]
void Motor::adjustMotor(Direction dirLeft, uint8_t powerLevelLeft, Direction dirRight, uint8_t powerLevelRight){

    // Led::setLed(Led::Color::RED);

    manageDirection(LEFT, dirLeft);
    manageDirection(RIGHT, dirRight);
    adjustPwm(powerLevelLeft, powerLevelRight);
}

void Motor::turnLeft(){
    adjustMotor(BACKWARD, TURN_SPEED, FORWARD, TURN_SPEED);
    _delay_ms(TIME_TURN_FAST);
    adjustMotor(BACKWARD, TURN_SPEED_SLOW, FORWARD, TURN_SPEED_SLOW);
    _delay_ms(TIME_TURN_SLOW);
    stop();
}

void Motor::turnRight(){
    adjustMotor(FORWARD, TURN_SPEED, BACKWARD, TURN_SPEED);
    _delay_ms(TIME_TURN_FAST);
    adjustMotor(FORWARD, TURN_SPEED_SLOW, BACKWARD, TURN_SPEED_SLOW);
    _delay_ms(TIME_TURN_SLOW);
    stop();
}

void Motor::turn180(){
    // fast
    adjustMotor(BACKWARD, TURN_SPEED, FORWARD, TURN_SPEED);
    _delay_ms(TIME_TURN_180_FAST);
    // slow
    adjustMotor(BACKWARD, TURN_SPEED_SLOW, FORWARD, TURN_SPEED_SLOW);
    _delay_ms(TIME_TURN_180_SLOW);
    stop();
}


void Motor::moveStraight(Direction dir, uint8_t powerLevel){
    // shift the power level to avoid overflow
    int8_t correction = forceCorrection;
    
    if(correction > MAX_SPEED - powerLevel){
        powerLevel = MAX_SPEED - correction;
    }

    uint8_t forceLeftWheel = powerLevel - correction;
    uint8_t forcerightWheel = powerLevel + correction;

    adjustMotor(dir, forceLeftWheel, dir, forcerightWheel);
}

// void Motor::moveStraight(Direction dir, uint8_t powerLevel){
//     adjustMotor(dir, powerLevel, dir, powerLevel);
// }

void Motor::stop(){
    adjustMotor(FORWARD,0,FORWARD,0);
}

void Motor::adjustForceCorrection(int8_t force){
    Motor::forceCorrection = force;
}
