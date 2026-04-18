#include "led.h"

#define LED_PORT PORTB
#define LED_DDR DDRB

volatile uint16_t Led::counter = 0;
volatile uint16_t Led::periodTicks = 0;
volatile uint16_t Led::flashesRemaining = 0;
volatile bool Led::flashing = false;
volatile Led::Color Led::currentColor = Led::OFF;
volatile bool Led::ledState = false;
volatile bool Led::amberToggle = false;

static const uint16_t AMBER_TICKS = 0;

void ledTimerHandler()
{
    if (Led::currentColor == Led::AMBER) {
        // off
        if (Led::flashing && !Led::ledState) {
            LED_PORT &= ~Led::RED_LED;
            LED_PORT &= ~Led::GREEN_LED;
        }
        else {
            // fix amber
            Led::amberToggle  = !Led::amberToggle;

            if (Led::amberToggle) {
                LED_PORT |=  Led::RED_LED;
                LED_PORT &= ~Led::GREEN_LED;
            }
            else {
                LED_PORT |=  Led::GREEN_LED;
                LED_PORT &= ~Led::RED_LED;
            }
        }
    }

    // flash on/off
    if (!Led::flashing) return;
    
    if (++Led::counter >= Led::periodTicks)
    {
        Led::counter  = 0;
        Led::ledState = !Led::ledState;
 
        if (Led::ledState) {
            if (Led::currentColor == Led::RED) {
                LED_PORT |=  Led::RED_LED;
                LED_PORT &= ~Led::GREEN_LED;
            }
            else if (Led::currentColor == Led::GREEN) {
                LED_PORT |=  Led::GREEN_LED;
                LED_PORT &= ~Led::RED_LED;
            }
        }
        else {
            if (Led::currentColor != Led::AMBER) {
                LED_PORT &= ~Led::RED_LED;
                LED_PORT &= ~Led::GREEN_LED;
            }
        }
    }
}

// beginning of led functions
void Led::init()
{
    LED_DDR |= RED_LED | GREEN_LED;
    LED_PORT &= ~RED_LED;
    LED_PORT &= ~GREEN_LED;
}

void Led::setLed(Color c)
{
    currentColor = c;
    amberToggle  = false;
 
    switch (c)
    {
        case RED:
            Timer8::stopTimer2();
            LED_PORT |=  RED_LED;
            LED_PORT &= ~GREEN_LED;
            break;
 
        case GREEN:
            Timer8::stopTimer2();
            LED_PORT |=  GREEN_LED;
            LED_PORT &= ~RED_LED;
            break;
 
        case AMBER:
            LED_PORT &= ~RED_LED;
            LED_PORT &= ~GREEN_LED;
            Timer8::startTimer2(
                Timer8::Clock2::DIV1024,
                Timer8::Mode::NORMAL,
                Timer8::CompareMode::DISCONNECTED,
                Timer8::CompareMode::DISCONNECTED,
                Timer8::Interrupt::OVERFLOW,
                ledTimerHandler);
            break;
 
        case OFF:
            Timer8::stopTimer2();
            LED_PORT &= ~RED_LED;
            LED_PORT &= ~GREEN_LED;
            break;
 
        default: // also off
            Timer8::stopTimer2();
            LED_PORT &= ~RED_LED;
            LED_PORT &= ~GREEN_LED;
            break;
    }
}

void Led::flash(Color c, uint16_t period_ms)
{
    Timer8::stopTimer2();
 
    currentColor = c;
    ledState = false;
    periodTicks = (period_ms * 1000ULL) / (TIMER0_OVERFLOW_US * 2);
    counter = 0;
    flashesRemaining = 0;
    flashing = true;
    amberToggle = false;
 
    Timer8::startTimer2(
        Timer8::Clock2::DIV1024,
        Timer8::Mode::NORMAL,
        Timer8::CompareMode::DISCONNECTED,
        Timer8::CompareMode::DISCONNECTED,
        Timer8::Interrupt::OVERFLOW,
        ledTimerHandler);
}

// static void flash(Color c, uint16_t period_ms, uint16_t nFlashes);

void Led::stopFlash()
{
    flashing = false;
    setLed(OFF);
    // Timer8::stopTimer0();
}