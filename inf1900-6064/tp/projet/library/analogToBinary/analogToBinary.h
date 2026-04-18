// Marc-Antoine Gaumond

// AnalogToBinary reads analog values via the onboard ADC and returns
// a binary value by discarding the least significant bits (2 bits)

#pragma once

#include <avr/io.h>
#include "can.h"

class AnalogToBinary {
public:
    static uint8_t readAtPin(uint8_t pin);

private:
    static constexpr uint8_t BITS_TO_IGNORE = 2;
};