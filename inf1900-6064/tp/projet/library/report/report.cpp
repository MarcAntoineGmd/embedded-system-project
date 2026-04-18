#include "report.h"

constexpr char Report::INITIAL_MSG[];
constexpr char Report::ROOM_A[];
constexpr char Report::ROOM_B[];
constexpr char Report::ROOM_C[];
constexpr char Report::ROOM_D[];
constexpr char Report::CORRIDOR_WEST[];
constexpr char Report::CORRIDOR_EAST[];
constexpr char Report::YES[];
constexpr char Report::NO[];
constexpr char Report::OBJECT[];
constexpr char Report::OBJECTS[];
constexpr char Report::PERSON[];
constexpr char Report::PEOPLE[];
constexpr char Report::DAMAGED_ZONE[];
constexpr char Report::DAMAGED_ZONES[];

void Report::generate()
{
    Led::init();
    Eeprom::init();

    playInitialSequence();
    
    uint8_t roomAData = Eeprom::readByte(ROOM_A_DATA_ADDR);
    uint8_t roomBData = Eeprom::readByte(ROOM_B_DATA_ADDR);
    uint8_t roomCData = Eeprom::readByte(ROOM_C_DATA_ADDR);
    uint8_t roomDData = Eeprom::readByte(ROOM_D_DATA_ADDR);
    uint8_t corridorWestData = Eeprom::readByte(CORRIDOR_WEST_DATA_ADDR);
    uint8_t corridorEastData = Eeprom::readByte(CORRIDOR_EAST_DATA_ADDR);

    Uart::transmitMessage(INITIAL_MSG);
    showData(ROOM_A, roomAData, PERSON, PEOPLE);
    showData(ROOM_B, roomBData, OBJECT, OBJECTS);
    showData(ROOM_C, roomCData, OBJECT, OBJECTS);
    showData(ROOM_D, roomDData, PERSON, PEOPLE);
    showData(CORRIDOR_WEST, corridorWestData, DAMAGED_ZONE, DAMAGED_ZONES);
    showData(CORRIDOR_EAST, corridorEastData, DAMAGED_ZONE, DAMAGED_ZONES);
}

void Report::showData(const char* roomName, uint8_t data, const char* singularElement, const char* pluralElement)
{
    Uart::transmitMessage(roomName);
    if (data <= COMPLIANCE_MAX_VALUE) {
        Uart::transmitMessage(YES);
        Uart::transmitNewLine();
    }
    else {
        Uart::transmitMessage(NO);
        Uart::transmitInteger(data);
        if (data >= PLURAL_MIN_VALUE) {
            Uart::transmitMessage(pluralElement);
        }
        else {
            Uart::transmitMessage(singularElement);
        }
        Uart::transmitNewLine();
    }
}

void Report::playInitialSequence()
{
    for (int i = 0; i < NB_START_FLASH; ++i) {
        Led::setLed(Led::Color::RED);
        _delay_ms(START_LED_TIME);
        Led::setLed(Led::Color::OFF);
        _delay_ms(START_LED_TIME);
    }
}