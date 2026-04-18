// Alexis Chapados

// Interpreter reads and executes a bytecode program stored in external EEPROM.
// Each two-byte instruction (opcode + operand) maps to a robot action such as
// motor movement, LED control, sound playback, wait, or loop constructs.

#pragma once

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "include.h"

enum class State {
    IDLE,
    STARTED,
    FINISHED
};

class Interpreter {
public:
    static void init();
    static void run();

private:
    static void readProgramSize();
    static void executeInstruction(uint8_t opcode, uint8_t operand);
    static void turnRight();
    static void turnLeft();

    static const uint8_t DATA_SIZE_BYTES = 2;
    
    static uint16_t currentAddress_;
    static uint16_t endAddr_;
    static uint16_t loopStartAddress_;
    static uint8_t  loopCounter_;
    static bool     isInLoop_;
    static State    state_;
};
