#pragma once
#include "include.h"

class Report
{
public:
    static void generate();

    static const uint16_t ROOM_A_DATA_ADDR = 0x0005;
    static const uint16_t ROOM_B_DATA_ADDR = 0x0006;
    static const uint16_t ROOM_C_DATA_ADDR = 0x0007;
    static const uint16_t ROOM_D_DATA_ADDR = 0x0008;
    static const uint16_t CORRIDOR_WEST_DATA_ADDR = 0x0009;
    static const uint16_t CORRIDOR_EAST_DATA_ADDR = 0x000A;

private:
    static void playInitialSequence();
    static void showData(const char* roomName, uint8_t data, const char* singularElement, const char* pluralElement);

    static constexpr char INITIAL_MSG[] = "Rapport de conformité\n\nEmplacement     Conformité     Détail\n--------------------------------------------------\n";
    static constexpr char ROOM_A[] = "Local A            ";
    static constexpr char ROOM_B[] = "Local B            ";
    static constexpr char ROOM_C[] = "Local C            ";
    static constexpr char ROOM_D[] = "Local D            ";
    static constexpr char CORRIDOR_WEST[] = "Couloir OUEST      ";
    static constexpr char CORRIDOR_EAST[] = "Couloir EST        ";
    
    static constexpr char YES[] = "oui";
    static constexpr char NO[] = "non         ";
    static constexpr char OBJECT[] = " objet";
    static constexpr char OBJECTS[] = " objets";
    static constexpr char PERSON[] = " personne";
    static constexpr char PEOPLE[] = " personnes";
    static constexpr char DAMAGED_ZONE[] = " zone endommagée";
    static constexpr char DAMAGED_ZONES[] = " zones endommagées";

    static const uint8_t NB_START_FLASH = 8;
    static const uint8_t START_LED_TIME = 125;
    static const uint8_t COMPLIANCE_MAX_VALUE = 0;
    static const uint8_t PLURAL_MIN_VALUE = 2;
};