#pragma once
#include <avr/io.h>
#include <util/delay.h>

class Button {
public:
    static void init();
    static bool isPressed();
private:
    static const uint8_t DEBOUNCE_DELAY = 20;
};