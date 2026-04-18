#include "interpreter.h"

uint16_t Interpreter::currentAddress_{};
uint16_t Interpreter::endAddr_{};
uint16_t Interpreter::loopStartAddress_{};
uint8_t  Interpreter::loopCounter_{};
bool     Interpreter::isInLoop_ = false;
State    Interpreter::state_{};

enum class Opcode : uint8_t {
    DBT = 0x01,
    ATT = 0x02,
    DAL = 0x44,
    DET = 0x45,
    SGO = 0x48,
    SAR = 0x09,
    MAR_STOP_1 = 0x60,
    MAR_STOP_2 = 0x61,
    MAV = 0x62,
    MRE = 0x63,
    TRD = 0x64,
    TRG = 0x65,
    DBC = 0xC0,
    FBC = 0xC1,
    FIN = 0xFF,
};

void Interpreter::init()
{
    currentAddress_ = Eeprom::FIRST_AVAILABLE_ADRESS;
}

void Interpreter::run()
{
    init();
    readProgramSize();
    state_ = State::IDLE;

    while (currentAddress_ < endAddr_) {
        uint8_t opcode = Eeprom::readByte(currentAddress_);
        uint8_t operand = Eeprom::readByte(currentAddress_ + 1);

        if (state_ == State::IDLE) {
            if (opcode == 0x01) {
                    state_ = State::STARTED;
                }
        }
        else {
            executeInstruction(opcode, operand);
            if (state_ == State::FINISHED) {
                break;
            }
        }

        currentAddress_ += DATA_SIZE_BYTES;
    }
}

void Interpreter::readProgramSize()
{
    uint8_t sizeHigh = Eeprom::readByte(currentAddress_);
    uint8_t sizeLow = Eeprom::readByte(currentAddress_ + 1);
    uint16_t programSize_ = (static_cast<uint16_t>(sizeHigh) << 8) | sizeLow;
    endAddr_ = Eeprom::FIRST_AVAILABLE_ADRESS + programSize_;
    currentAddress_ += DATA_SIZE_BYTES;
}

void Interpreter::executeInstruction(uint8_t opcode, uint8_t operand)
{
    switch (static_cast<Opcode>(opcode)) {
        case Opcode::DBT:
            break;

        case Opcode::ATT:
            for (uint8_t i = 0; i < operand; i++) {
                _delay_ms(25);
            }
            break;

        case Opcode::DAL:
            if (operand == 1) {
                Led::setLed(Led::GREEN);
            } else if (operand == 2) {
                Led::setLed(Led::RED);
            }
            break;

        case Opcode::DET:
            Led::setLed(Led::OFF);
            break;

        case Opcode::SGO:
            Speaker::play(operand);
            break;

        case Opcode::SAR:
            Speaker::stop();
            break;

        case Opcode::MAR_STOP_1:
        case Opcode::MAR_STOP_2:
            Motor::moveStraight(Motor::FORWARD, 0);
            break;

        case Opcode::MAV:
            Motor::moveStraight(Motor::FORWARD, operand);
            break;

        case Opcode::MRE:
            Motor::moveStraight(Motor::BACKWARD, operand);
            break;

        case Opcode::TRD:
            Motor::turnRight();
            break;

        case Opcode::TRG:
            Motor::turnLeft();
            break;

        case Opcode::DBC:
            loopStartAddress_ = currentAddress_;
            loopCounter_ = operand;
            isInLoop_ = true;
            break;

        case Opcode::FBC:
            if (isInLoop_ && loopCounter_ > 0) {
                loopCounter_--;
                currentAddress_ = loopStartAddress_;
            } else {
                isInLoop_ = false;
            }
            break;

        case Opcode::FIN:
            state_ = State::FINISHED;
            break;

        default:
            break;
    }
}
