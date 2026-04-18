// Frédéric Labelle

// Uart configures USART0 for 9600 baud serial communication.
// Provides blocking transmit and receive for characters, strings, and integers.

#pragma once
#include <stdlib.h>
#include <avr/io.h>

class Uart
{
public:
    static void init();
    static void transmitMessage(const char* donnees);
    static void transmitInteger(int16_t valeur);
    static void transmitNewLine();
    static uint8_t receiveChar();

private:
    static void transmitChar(const char donnee);
    static const uint8_t DECIMAL_BASE = 10;
    static const uint8_t MAX_INT16_STR_SIZE = 7;
    static const char NEW_LINE = '\n';
};