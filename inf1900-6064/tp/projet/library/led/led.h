// Marc-Antoine Gaumond

// Led provides a static interface for controlling a dual-color red/green LED on PORTB.
// Supports solid colors, amber simulation via rapid use of Timer0 for toggling, and
// flashing. All state is managed through static members and a friend ISR handler.

#pragma once

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "timer/timer.h"

void ledTimerHandler();

class Led
{
public:
    static constexpr uint8_t GREEN_LED = (1 << PB0);
    static constexpr uint8_t RED_LED   = (1 << PB1);

    enum Color {
        RED,
        GREEN,
        AMBER,
        OFF
    };

    static void init();
    static void setLed(Color c);
    static void flash(Color c, uint16_t period_ms);
    // static void flash(Color c, uint16_t period_ms, uint16_t nFlashes);
    static void stopFlash();

private:
    friend void ledTimerHandler();
    
    static volatile uint16_t counter;
    static volatile uint16_t periodTicks;
    static volatile uint16_t flashesRemaining;
    static volatile bool flashing;
    static volatile Color currentColor;
    static volatile bool ledState;
    static volatile bool amberToggle;

    static constexpr uint32_t CPU_FREQ_HZ = 8000000UL;
    static constexpr uint32_t TIMER0_PRESCALER = 1024;
    static constexpr uint16_t TIMER0_MAX = 256;

    static constexpr uint32_t TIMER0_OVERFLOW_US = (TIMER0_PRESCALER * TIMER0_MAX * 1000000ULL) / CPU_FREQ_HZ;

    // static volatile bool amberToggle;
};