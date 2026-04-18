#include "timer.h"

static void (*timer0Callback)() = nullptr;
static void (*timer2Callback)() = nullptr;

uint8_t Timer8::modeToWGM(Mode m)
{
    switch(m) {
        case Mode::NORMAL:
            return 0;
        case Mode::PWM_PHASE_CORRECT:
            return (1 << WGM00);
        case Mode::CTC:
            return (1 << WGM01);
        case Mode::FAST_PWM:
            return (1 << WGM01) | (1 << WGM00);
    }
    return 0;
}

uint8_t Timer8::compareToCOM(CompareMode c)
{
    switch(c) {
        case CompareMode::DISCONNECTED:
            return 0;
        case CompareMode::TOGGLE:
            return 1;
        case CompareMode::CLEAR:
            return 2;
        case CompareMode::SET:
            return 3;
    }
    return 0;
}

uint8_t Timer8::clockToCS(Clock c)
{
    switch(c) {
        case Clock::STOP:
            return 0;
        case Clock::NO_PRESCALE:
            return 1;
        case Clock::DIV8:
            return 2;
        case Clock::DIV64:
            return 3;
        case Clock::DIV256:
            return 4;
        case Clock::DIV1024:
            return 5;
    }
    return 0;
}

uint8_t Timer8::clockToCS2(Clock2 c)
{
    switch(c) {
        case Clock2::STOP:
            return 0;
        case Clock2::NO_PRESCALE:
            return 1;
        case Clock2::DIV8:
            return 2;
        case Clock2::DIV32:
            return 3;
        case Clock2::DIV64:
            return 4;
        case Clock2::DIV128:
            return 5;
        case Clock2::DIV256:
            return 6;
        case Clock2::DIV1024:
            return 7;
    }
    return 0;
}

// TIMER 0

void Timer8::startTimer0(Clock clk, Mode mode, CompareMode comA, CompareMode comB, Interrupt it, void (*func)())
{
    cli();

    stopTimer0();

    TCCR0A = 0;
    
    TCCR0B = 0;

    TCCR0A |= modeToWGM(mode);
    // as said, we do not use the WGM bit in TCCRnB

    // A
    TCCR0A |= (compareToCOM(comA) << COM0A0);

    // B
    TCCR0A |= (compareToCOM(comB) << COM0B0);

    // prescaler
    TCCR0B |= clockToCS(clk);

    // timer interruptions
    TIMSK0 = 0;

    switch(it) {
        case Interrupt::OVERFLOW:
            TIMSK0 |= (1 << TOIE0);
            break;
        case Interrupt::COMPARE_A:
            TIMSK0 |= (1 << OCIE0A);
            break;
        case Interrupt::COMPARE_B:
            TIMSK0 |= (1 << OCIE0B);
            break;
        default:
            break;
    }

    if (it != Interrupt::NONE)
        timer0Callback = func; // pointer on function
    else
        timer0Callback = nullptr;

    sei();
}

void Timer8::startTimer0(Clock clk, Mode mode, CompareMode comA, CompareMode comB)
{
    startTimer0(clk, mode, comA, comB, Interrupt::NONE, [](){}); // no interrupt & no func
}

void Timer8::stopTimer0()
{
    TCCR0B = 0;
    TIMSK0 = 0;
    timer0Callback = nullptr;
    TCNT0 = 0;
}

bool Timer8::timer0IsActive()
{
    return (TCCR0B & 0x07) != 0; // if CS02:0 = 0, timer is stopped
}

// TIMER 2

void Timer8::startTimer2(Clock2 clk, Mode mode, CompareMode comA, CompareMode comB, Interrupt it, void (*func)())
{    
    cli();

    stopTimer2();

    TCCR2A = 0;
    TCCR2B = 0;

    TCCR2A |= modeToWGM(mode);

    TCCR2A |= (compareToCOM(comA) << COM2A0);
    TCCR2A |= (compareToCOM(comB) << COM2B0);

    TCCR2B |= clockToCS2(clk);

    TIMSK2 = 0;

    switch(it) {
        case Interrupt::OVERFLOW:
            TIMSK2 |= (1 << TOIE2);
            break;
        case Interrupt::COMPARE_A:
            TIMSK2 |= (1 << OCIE2A);
            break;
        case Interrupt::COMPARE_B:
            TIMSK2 |= (1 << OCIE2B);
            break;
        default:
            break;
    }

    if (it != Interrupt::NONE)
        timer2Callback = func;
    else
        timer2Callback = nullptr;

    sei();
}

void Timer8::startTimer2(Clock2 clk, Mode mode, CompareMode comA, CompareMode comB)
{
    startTimer2(clk, mode, comA, comB, Interrupt::NONE, [](){});
}

void Timer8::stopTimer2()
{
    TCCR2B = 0;
    TIMSK2 = 0;
    timer2Callback = nullptr;
    TCNT2 = 0;
}

bool Timer8::timer2IsActive()
{
    return (TCCR2B & 0x07) != 0;
}

// ISR

ISR(TIMER0_OVF_vect)
{
    if (timer0Callback)
        timer0Callback();
}

ISR(TIMER0_COMPA_vect)
{
    if (timer0Callback)
        timer0Callback();
}

ISR(TIMER0_COMPB_vect)
{
    if (timer0Callback)
        timer0Callback();
}

ISR(TIMER2_OVF_vect)
{
    if (timer2Callback)
        timer2Callback();
}

ISR(TIMER2_COMPA_vect)
{
    if (timer2Callback)
        timer2Callback();
}

ISR(TIMER2_COMPB_vect)
{
    if (timer2Callback)
        timer2Callback();
}