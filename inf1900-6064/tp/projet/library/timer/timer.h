// Marc-Antoine Gaumond

// Timer8 provides a static interface for configuring and controlling
// the 8-bit timers (Timer0 and Timer2). Handles prescaler,
// waveform mode, compare output mode, and interrupt routing via callbacks.

#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

class Timer8 {
public:

    // (WGM02:0)
    enum class Mode {
        NORMAL,
        PWM_PHASE_CORRECT,
        CTC,
        FAST_PWM
    };

    // (COMxA1:0 / COMxB1:0) (it's the same thing for both, but controls two pairs of different pins)
    // OCnA and OCnB
    enum class CompareMode {
        DISCONNECTED,
        TOGGLE,
        CLEAR,
        SET
    };

    // (CS02:0) (prescaler) (used for Timer0)
    enum class Clock {
        STOP,
        NO_PRESCALE,
        DIV8,
        DIV64,
        DIV256,
        DIV1024
    };

    // (CS02:0) (prescaler) (used for Timer2)
    enum class Clock2 {
        STOP,
        NO_PRESCALE,
        DIV8,
        DIV32, // Timer2
        DIV64,
        DIV128, // Timer2
        DIV256,
        DIV1024
    };

    enum class Interrupt {
        NONE,
        OVERFLOW,
        COMPARE_A,
        COMPARE_B
    };

    // TIMER 0

    static void startTimer0(Clock clk, Mode mode, CompareMode comA, CompareMode comB, Interrupt it, void (*func)());

    static void startTimer0(Clock clk, Mode mode, CompareMode comA, CompareMode comB);

    static void stopTimer0();

    static bool timer0IsActive();

    // TIMER 2

    static void startTimer2(Clock2 clk, Mode mode, CompareMode comA, CompareMode comB, Interrupt it, void (*func)());

    static void startTimer2(Clock2 clk, Mode mode, CompareMode comA, CompareMode comB);

    static void stopTimer2();

    static bool timer2IsActive();

private:

    // those functions are used to transform the variables in the enum, into real changes of the registers

    // we only use wgm bits (of the 3), since normal, ctc, fast pwm and
    // pwm phase correct only use 2 (the 3rd is always set to 0)
    static uint8_t modeToWGM(Mode m); // wgm bits in TCCRnA

    static uint8_t compareToCOM(CompareMode c);

    static uint8_t clockToCS(Clock c);
    
    // the prescalers for the timer 2 are different than the ones for timer 0
    static uint8_t clockToCS2(Clock2 c);
};
