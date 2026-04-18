// Frédéric Labelle

// Eeprom wraps the 24CXXX external I2C memory chip with a sequential string store.
// Tracks a persistent write cursor across resets and supports raw byte and 16-bit access.

#pragma once
#include "memoire_24.h"

class Eeprom
{
public:
    static void init();
    static uint16_t writeByte(uint8_t byte);
    static void writeByte(uint8_t byte, uint16_t address);
    static uint8_t readByte(uint16_t address);

    static const uint16_t FIRST_AVAILABLE_ADRESS = 0x0000;

private:
    static Memoire24CXXX memory_;
    static uint16_t currentAdress_;
};