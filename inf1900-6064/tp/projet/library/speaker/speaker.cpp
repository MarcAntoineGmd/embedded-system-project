#include "speaker.h"

#define OCR_NOTE(prescaler, freq) \
    (uint8_t)(Speaker::F_CPU_HZ / (2UL * (prescaler) * (freq)) - 1)



const uint8_t Speaker::NOTES_OCR[] PROGMEM =
{
    OCR_NOTE(256, 110), // 45
    OCR_NOTE(256, 117), // 46
    OCR_NOTE(256, 123), // 47
    OCR_NOTE(256, 131), // 48
    OCR_NOTE(128, 139), // 49
    OCR_NOTE(128, 147), // 50
    OCR_NOTE(128, 156), // 51
    OCR_NOTE(128, 165), // 52
    OCR_NOTE(128, 175), // 53
    OCR_NOTE(128, 185), // 54
    OCR_NOTE(128, 196), // 55
    OCR_NOTE(128, 208), // 56
    OCR_NOTE(128, 220), // 57
    OCR_NOTE(128, 233), // 58
    OCR_NOTE(128, 247), // 59
    OCR_NOTE(128, 262), // 60
    OCR_NOTE(128, 277), // 61
    OCR_NOTE(128, 294), // 62
    OCR_NOTE(128, 311), // 63
    OCR_NOTE(128, 330), // 64
    OCR_NOTE(128, 349), // 65
    OCR_NOTE(128, 370), // 66
    OCR_NOTE(128, 392), // 67
    OCR_NOTE(128, 415), // 68
    OCR_NOTE(128, 440), // 69
    OCR_NOTE(128, 466), // 70
    OCR_NOTE(128, 494), // 71
    OCR_NOTE(128, 523), // 72
    OCR_NOTE(128, 554), // 73
    OCR_NOTE(128, 587), // 74
    OCR_NOTE(128, 622), // 75
    OCR_NOTE(128, 659), // 76
    OCR_NOTE(128, 698), // 77
    OCR_NOTE(128, 740), // 78
    OCR_NOTE(128, 784), // 79
    OCR_NOTE(128, 831), // 80
    OCR_NOTE(128, 880), // 81
};

#undef OCR_NOTE

void Speaker::init()
{
    DDRD |=  (1 << PD7);

    DDRD  |=  (1 << PD6);
    PORTD &= ~(1 << PD6);

    TCCR2A = 0;
    TCCR2B = 0;
}

void Speaker::play(uint8_t noteMidi)
{
    if (noteMidi < NOTE_MIN || noteMidi > NOTE_MAX)
        return;

    uint8_t ocr = pgm_read_byte(&NOTES_OCR[noteMidi - NOTE_MIN]);
    
    OCR2A = ocr;

    Timer8::startTimer2(
        noteMidi <= NOTE_SEUIL_256 ? Timer8::Clock2::DIV256 : Timer8::Clock2::DIV128,
        Timer8::Mode::CTC,
        Timer8::CompareMode::TOGGLE,
        Timer8::CompareMode::DISCONNECTED);
}

void Speaker::stop()
{
    TCCR2B = 0;
    TCCR2A = 0;
    PORTD &= ~(1 << PD7);
}