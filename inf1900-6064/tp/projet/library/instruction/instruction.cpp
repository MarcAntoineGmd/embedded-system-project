#include "instruction.h"

void Instruction::receive()
{
    playInitialSequence();

    skipByte(); // Size                                              TEMPORAIRE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    skipByte();

    skipByte(); // dbt
    skipByte();

    uint8_t val = Uart::receiveChar(); // tr
    Eeprom::writeByte(val & DIRECTION_BIT, DIRECTION_ADDR);
    skipByte();

    skipByte(); // sgo 1
    readByte(NOTE1_ADDR);

    skipByte(); // sgo 2
    readByte(NOTE2_ADDR);

    skipByte(); // sgo 3
    readByte(NOTE3_ADDR);

    skipByte(); // att
    readByte(PARKING_ADDR);

    skipByte(); // fin
    skipByte();

    playFinalSequence();
}

void Instruction::readByte(uint16_t storeAdress)
{
    uint8_t val = Uart::receiveChar();

    while (EECR & (1 << EEPE)) {} // Memory is ready?
    Eeprom::writeByte(val, storeAdress);
}

void Instruction::skipByte()
{
    Uart::receiveChar();
}

void Instruction::playInitialSequence()
{
    for (int i = 0; i < NB_START_FLASH; ++i) {
        Led::setLed(Led::GREEN);
        _delay_ms(START_LED_TIME);
        Led::setLed(Led::OFF);
        _delay_ms(START_LED_TIME);
    }
}

void Instruction::playFinalSequence()
{
    uint8_t n1 = Eeprom::readByte(NOTE1_ADDR);
    _delay_ms(5);
    uint8_t n2 = Eeprom::readByte(NOTE2_ADDR);
    _delay_ms(5);
    uint8_t n3 = Eeprom::readByte(NOTE3_ADDR);
    _delay_ms(5);
    uint8_t direction = Eeprom::readByte(DIRECTION_ADDR);
    _delay_ms(5);
    uint8_t parkingSlot = Eeprom::readByte(PARKING_ADDR);
    _delay_ms(5);

    Speaker::play(n1);
    _delay_ms(SOUND_ON_TIME);
    Speaker::stop();
    _delay_ms(SOUND_OFF_TIME);

    Speaker::play(n2);
    _delay_ms(SOUND_ON_TIME);
    Speaker::stop();
    _delay_ms(SOUND_OFF_TIME);

    Speaker::play(n3);
    _delay_ms(SOUND_ON_TIME);
    Speaker::stop();

    _delay_ms(PAUSE_TIME);

    if (direction == RIGHT) {
        Led::setLed(Led::GREEN);
    }
    else {
        Led::setLed(Led::RED);
    }
    _delay_ms(DIRECTION_LED_TIME);
    Led::setLed(Led::OFF);

    _delay_ms(PAUSE_TIME);

    for (int i = 0; i < parkingSlot; ++i) {
        Led::setLed(Led::AMBER);
        _delay_ms(PARKING_LED_TIME);
        Led::setLed(Led::OFF);
        _delay_ms(PARKING_LED_TIME);
    }
}