#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "library/include.h"


int main(){
    Uart::init();
    LineSensor::init();
    // InfraredSensor::init();
    // while (true)
    // {
    //     uint16_t val = InfraredSensor::getDistance();

    //     DEBUG_PRINT_INT(val);
    //     DEBUG_PRINT_NEW_LINE();
    //     _delay_ms(1000);
    // }  

    
    
}