// Debug provides conditional UART logging macros controlled by the DEBUG compile flag.
// When DEBUG is undefined, all macros compile to no-ops with zero runtime overhead.

#pragma once

#ifdef DEBUG
    #include "uart/uart.h"
    #define DEBUG_PRINT_MSG(msg) Uart::transmitMessage(msg)
    #define DEBUG_PRINT_INT(val) Uart::transmitInteger(val)
    #define DEBUG_PRINT_NEW_LINE() Uart::transmitNewLine()
#else
    #define DEBUG_PRINT_MSG(msg) do {} while(0)
    #define DEBUG_PRINT_INT(val) do {} while(0)
    #define DEBUG_PRINT_NEW_LINE(val) do {} while(0)
#endif