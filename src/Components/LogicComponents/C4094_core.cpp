/*
** EPITECH PROJECT, 2021
** C4094_CORE
** File description:
** C4094_core class (8 bits shift register)
*/

#include <string.h>
#include <math.h>
#include <C4094_core.hpp>

#define CLOCK_PIN 3
#define DATA_PIN 2
#define STROBE_PIN 1
#define ENABLE_PIN 15

#define OUT_QS_PIN 9
#define OUT_QE_PIN 10

namespace nts
{
    int C4094_core::nbPinOut = 8;
    int C4094_core::pinOutId[8] = {4, 5, 6, 7, 14, 13, 12, 11};

    C4094_core::C4094_core(std::string name) : AComponent("4094_core", name)
    {
        ADD_PIN_IN(CLOCK_PIN);  // clock
        ADD_PIN_IN(DATA_PIN);   // data
        ADD_PIN_IN(STROBE_PIN); // strobe
        ADD_PIN_IN(ENABLE_PIN); // enable
        for (int out = 0; out < nbPinOut; out++)
            ADD_PIN_OUT(pinOutId[out]); // out_n

        ADD_PIN_OUT(OUT_QS_PIN); // out_qs
        ADD_PIN_OUT(OUT_QE_PIN); // out_qe

        _lastClockState = UNDEFINED;
        for (int k = 0; k < nbPinOut; k++)
            _data.push_back(UNDEFINED);
    }

    C4094_core::~C4094_core()
    {
    }

    void C4094_core::simulate(std::size_t tick)
    {
        if (getPin(ENABLE_PIN)->getState() == TRUE)
        {
            if (getPin(STROBE_PIN)->getState() == TRUE && _lastClockState == FALSE && getPin(CLOCK_PIN)->getState() == TRUE) // strobe == TRUE && clock 0 -> 1
            {
                // shift data
                _data.insert(_data.begin(), getPin(DATA_PIN)->getState());
                _data.pop_back();
            }

            // write data
            for (int out = 0; out < nbPinOut; out++)
                getPin(pinOutId[out])->setState(_data[out]);
        }
        else
        {
            // write undefined
            for (int out = 0; out < nbPinOut; out++)
                getPin(pinOutId[out])->setState(UNDEFINED);
        }

        // update QS and QE
        if (_lastClockState == FALSE && getPin(CLOCK_PIN)->getState() == TRUE) // clock 0 -> 1
            getPin(OUT_QS_PIN)->setState(getPin(pinOutId[nbPinOut - 2])->getState());
        else if (_lastClockState == TRUE && getPin(CLOCK_PIN)->getState() == FALSE) // clock 1 -> 0
            getPin(OUT_QE_PIN)->setState(getPin(pinOutId[nbPinOut - 2])->getState());

        _lastClockState = getPin(CLOCK_PIN)->getState();
        AComponent::simulate(tick);
    }

} // namespace nts