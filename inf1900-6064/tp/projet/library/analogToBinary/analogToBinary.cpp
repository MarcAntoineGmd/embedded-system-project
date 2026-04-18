#include "analogToBinary.h"

uint8_t AnalogToBinary::readAtPin(uint8_t pin)
{
    static Can adc;

    uint16_t value = adc.lecture(pin);

    return static_cast<uint8_t>(value >> BITS_TO_IGNORE);
}