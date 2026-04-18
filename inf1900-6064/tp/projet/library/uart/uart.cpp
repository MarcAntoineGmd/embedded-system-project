#include "uart.h"

void Uart::init()
{
    UBRR0H = 0;
    UBRR0L = 0xCF;

    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void Uart::transmitChar(const char data)
{
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = data;
}

void Uart::transmitMessage(const char* data)
{
    while (*data) {
        transmitChar(*data++);
    }
}

void Uart::transmitNewLine()
{
    transmitChar(NEW_LINE);
}

void Uart::transmitInteger(int16_t value)
{
    char buffer[MAX_INT16_STR_SIZE];
    
    itoa(value, buffer, DECIMAL_BASE); 
    
    transmitMessage(buffer);
}

uint8_t Uart::receiveChar()
{
    while (!(UCSR0A & (1 << RXC0))) {}
    return UDR0;
}