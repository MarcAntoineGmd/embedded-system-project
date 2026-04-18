#pragma once
#include "include.h"

class Instruction
{
public:
    static void receive();

    static const uint16_t DIRECTION_ADDR = 0x0000;
    static const uint16_t NOTE1_ADDR = 0x0001;
    static const uint16_t NOTE2_ADDR = 0x0002;
    static const uint16_t NOTE3_ADDR = 0x0003;
    static const uint16_t PARKING_ADDR = 0x0004;

private:
    static void readByte(uint16_t storeAdress);
    static void skipByte();
    static void playInitialSequence();
    static void playFinalSequence();


    static const uint8_t DIRECTION_BIT = 0x01;

    static const uint8_t NB_START_FLASH = 8;
    static const uint8_t START_LED_TIME = 125;
    static const uint8_t SOUND_ON_TIME = 250;
    static const uint8_t SOUND_OFF_TIME = 125;
    static const uint16_t DIRECTION_LED_TIME = 2000;
    static const uint16_t PAUSE_TIME = 2000;
    static const uint8_t RIGHT = 0;
    static const uint8_t LEFT = 1;
    static const uint16_t PARKING_LED_TIME = 500;
};