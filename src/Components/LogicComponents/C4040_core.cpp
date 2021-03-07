/*
** EPITECH PROJECT, 2021
** C4040_CORE
** File description:
** C4040_CORE class (12 bits counter)
*/

#include <string.h>
#include <math.h>
#include <C4040_core.hpp>

#define CLOCK_PIN 10
#define RESET_PIN 11

namespace nts
{
    int C4040_core::nbPinOut = 12;
    int C4040_core::pinOutId[12] = {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1};

    C4040_core::C4040_core(std::string name) : AComponent("4040_core", name)
    {
        ADD_PIN_IN(CLOCK_PIN); // clock
        ADD_PIN_IN(RESET_PIN); // reset
        for (int out = 0; out < nbPinOut; out++)
            ADD_PIN_OUT(pinOutId[out]); // out_n

        _lastClockState = UNDEFINED;
        _count = -1;
    }

    C4040_core::~C4040_core()
    {
    }

    void C4040_core::simulate(std::size_t tick)
    {
        // handle clock
        if (_count != -1 && _lastClockState == TRUE && getPin(CLOCK_PIN)->getState() == FALSE)
            _count++;
        _lastClockState = getPin(CLOCK_PIN)->getState();

        // handle reset
        if (getPin(RESET_PIN)->getState() == TRUE)
            _count = 0;

        // write output
        for (int out = 0; out < nbPinOut; out++)
        {
            // write undefined
            if (_count == -1)
                getPin(pinOutId[out])->setState(UNDEFINED);
            else
            {
                // write count
                if (_count >> out & 0b1)
                    getPin(pinOutId[out])->setState(TRUE);
                else
                    getPin(pinOutId[out])->setState(FALSE);
            }
        }

        AComponent::simulate(tick);
    }

} // namespace nts