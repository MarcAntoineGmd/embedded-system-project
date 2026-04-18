#include "eeprom.h"

Memoire24CXXX Eeprom::memory_;
uint16_t Eeprom::currentAdress_;

void Eeprom::init()
{
    currentAdress_ = FIRST_AVAILABLE_ADRESS;
}

uint16_t Eeprom::writeByte(uint8_t byte)
{
    memory_.write(currentAdress_, byte);
    uint16_t byteAdress = currentAdress_;
    ++currentAdress_;
    return byteAdress;
}

void Eeprom::writeByte(uint8_t byte, uint16_t adress)
{
    memory_.write(adress, byte);
}

uint8_t Eeprom::readByte(uint16_t address)
{
    uint8_t byte;
    memory_.read(address, &byte);
    return byte;
}