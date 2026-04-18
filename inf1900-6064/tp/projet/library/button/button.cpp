#include "button.h"

void Button::init() {
    DDRD &= ~(1 << PD2);
}

bool Button::isPressed() {
    if (PIND & (1 << PD2)) {
        _delay_ms(DEBOUNCE_DELAY);
        return (PIND & (1 << PD2));
    }
    return false;
}