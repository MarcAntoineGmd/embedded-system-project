#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "library/include.h"

static const uint8_t BTN_POLLING_INTERVAL = 20;
static const uint16_t INITIAL_DELAY = 2000;
static const uint16_t PAUSE_DELAY = 1000;
static const uint8_t LED_ON_LOOP_COUNT = 100;

// enum class Mode : uint8_t {
//     INSTRUCTION,
//     EXECUTE,
//     REPORT,
// };

// Mode selectMode();

static const uint16_t DELAY_BETWEEN_TURNS = 1000;

void test180(){
    while(true){
        Motor::turn180();
        _delay_ms(DELAY_BETWEEN_TURNS);
    }
}

void test90(){
    while(true){
        Motor::turnLeft();
        _delay_ms(DELAY_BETWEEN_TURNS);
        Motor::turnRight();
        _delay_ms(DELAY_BETWEEN_TURNS);
    }
}

int main()
{
    Uart::init();
    Led::init();
    Motor::init();
    Speaker::init();
    Eeprom::init();
    Button::init();

    Motor::adjustForceCorrection(6);

    _delay_ms(2000);

    // Movement::goRight(); // si goingRight = true

    //Movement::park(0); // changer 1 à 2, 3, ou 4 pour tester les autres places

    //test180();

    //test90();

    // entire parkour
    Movement::checkCorridor1();
    _delay_ms(1000);
    Movement::goToNextRoom();
    _delay_ms(1000);
    Movement::goToNextRoom();
    _delay_ms(1000);
    Movement::goToNextRoom();
    _delay_ms(1000);
    Movement::checkCorridor2(0);


    // Mode mode = selectMode();

    // switch (mode) {
    //     case Mode::INSTRUCTION:
    //         Instruction::receive();
    //         break;

    //     case Mode::EXECUTE:
    //         Led::flash(Led::RED, 500);
    //         break;

    //     case Mode::REPORT:
    //         Report::generate();
    //         break;

    //     default:
    //         break;
    // }

    // while (true) {}
}

// Mode selectMode()
// {
//     _delay_ms(INITIAL_DELAY);

//     Led::setLed(Led::GREEN);
//     for (uint16_t i = 0; i < LED_ON_LOOP_COUNT; i++) {
//         if (Button::isPressed()) {
//             Led::setLed(Led::OFF);
//             return Mode::INSTRUCTION;
//         }
//         _delay_ms(BTN_POLLING_INTERVAL);
//     }

//     Led::setLed(Led::OFF);
//     _delay_ms(PAUSE_DELAY);

//     Led::setLed(Led::RED);
//     for (uint16_t i = 0; i < LED_ON_LOOP_COUNT; i++) {
//         if (Button::isPressed()) {
//             Led::setLed(Led::OFF);
//             return Mode::REPORT;
//         }
//         _delay_ms(BTN_POLLING_INTERVAL);
//     }

//     Led::setLed(Led::OFF);
//     _delay_ms(PAUSE_DELAY);

//     return Mode::EXECUTE;
// }