// Central include header that aggregates all hardware driver and utility modules.
// Include this file in translation units that need access to the full component set.

#pragma once

#include "analogToBinary/analogToBinary.h"
#include "button/button.h"
#include "eeprom/eeprom.h"
#include "instruction/instruction.h"
#include "interpreter/interpreter.h"
#include "led/led.h"
#include "lineSensor/lineSensor.h"
#include "infraredSensor/infraredSensor.h"
#include "motor/motor.h"
#include "report/report.h"
#include "speaker/speaker.h"
#include "timer/timer.h"
#include "uart/uart.h"
#include "debug.h"
#include "movement/movement.h"