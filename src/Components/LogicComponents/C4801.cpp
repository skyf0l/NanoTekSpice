/*
** EPITECH PROJECT, 2021
** C4801
** File description:
** C4801 class (Random access memory)
*/

#include <string.h>
#include <math.h>
#include <C4801.hpp>

#define ENABLE_PIN 18
#define READ_PIN 20
#define WRITE_PIN 21

namespace nts
{
    int C4801::nbPinIn = 10;
    int C4801::nbPinIO = 8;
    int C4801::pinInId[10] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
    int C4801::pinIOId[8] = {9, 10, 11, 13, 14, 15, 16, 17};

    C4801::C4801(std::string name) : AComponent("4801", name)
    {
        ADD_PIN_IN(ENABLE_PIN); // enable
        ADD_PIN_IN(READ_PIN);   // read
        ADD_PIN_IN(WRITE_PIN);  // write

        for (int in = 0; in < nbPinIn; in++)
            ADD_PIN_IN(pinInId[in]); // addr_n
        for (int io = 0; io < nbPinIO; io++)
            ADD_PIN_IO(pinIOId[io]); // io_n

        _ram = new char[1024 * 8];
        memset(_ram, 0, 1024 * 8);
    }

    C4801::~C4801()
    {
        if (_ram)
            delete[] _ram;
    }

    void C4801::simulate(std::size_t tick)
    {
        // read addr
        int addr = 0;
        for (int in = 0; in < nbPinIn; in++)
        {
            Tristate pinValue = getPin(pinInId[in])->getState();
            if (pinValue == TRUE)
                addr += std::pow(2, in);
            else if (pinValue == UNDEFINED)
            {
                addr = -1;
                break;
            }
        }

        if (addr == -1 || getPin(ENABLE_PIN)->getState() == TRUE || (getPin(ENABLE_PIN)->getState() == FALSE && getPin(READ_PIN)->getState() == TRUE && getPin(WRITE_PIN)->getState() == TRUE))
        {
            // write undefined
            for (int out = 0; out < nbPinIO; out++)
                getPin(pinIOId[out])->setState(UNDEFINED);
        }
        else if (getPin(WRITE_PIN)->getState() == FALSE)
        {
            // write in rom
            char byte = 0;
            // read byte
            for (int in = 0; in < nbPinIO; in++)
            {
                Tristate pinValue = getPin(pinIOId[in])->getState();
                if (pinValue == TRUE)
                    byte += std::pow(2, in);
                else if (pinValue == UNDEFINED)
                {
                    // write undefined
                    for (int out = 0; out < nbPinIO; out++)
                        getPin(pinIOId[out])->setState(UNDEFINED);
                    break;
                }
            }

            _ram[addr] = byte;
        }
        else
        {
            // read from rom
            char byte = _ram[addr];

            // write readed byte
            for (int out = 0; out < nbPinIO; out++)
            {
                if (byte >> out & 0b1)
                    getPin(pinIOId[out])->setState(TRUE);
                else
                    getPin(pinIOId[out])->setState(FALSE);
            }
        }

        AComponent::simulate(tick);
    }

} // namespace nts