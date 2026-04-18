// Marc-Antoine Gaumond

// Speaker controls a piezo buzzer on PD7 using Timer2 in CTC/toggle mode.
// Supports MIDI note playback via a precomputed OCR table stored in program memory,
// spanning two prescaler ranges to cover the full note range.

#pragma once

#include <avr/io.h>
#include <avr/pgmspace.h> // progmem
#include <stdint.h>

#include <include.h>

class Speaker
{
public:
    static void init();

    static void play(uint8_t noteMidi);

    static void stop();

    static constexpr uint32_t F_CPU_HZ = 8000000UL;

    static constexpr uint8_t NOTE_MIN = 45;
    static constexpr uint8_t NOTE_MAX = 81;
    static constexpr uint8_t NOTE_SEUIL_256 = 48;

private:
    static const uint8_t NOTES_OCR[] PROGMEM;
};