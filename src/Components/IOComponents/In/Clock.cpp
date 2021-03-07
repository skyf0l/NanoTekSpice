/*
** EPITECH PROJECT, 2021
** CLOCK
** File description:
** Clock class
*/

#include <Clock.hpp>

namespace nts
{
    Clock::Clock(std::string name) : AComponent("clock", name, INPUT)
    {
        ADD_PIN_OUT(1);
        _nextState = UNDEFINED;
    }

    Clock::~Clock()
    {
    }

    void Clock::simulate(std::size_t tick)
    {
        getPin(1)->setState(_nextState);
        AComponent::simulate(tick);
        compute(1);
        if (getPin(1)->getState() == TRUE)
            _nextState = FALSE;
        else if (getPin(1)->getState() == FALSE)
            _nextState = TRUE;
    }

    void Clock::setValue(Tristate value)
    {
        getPin(1)->setState(value);
        _nextState = value;
    }

    void Clock::setValue(std::string value)
    {
        try
        {
            getPin(1)->setState(stringToTristate(value));
            _nextState = stringToTristate(value);
        }
        catch (InvalidValueException &)
        {
            throw InvalidValueException("\"" + value + "\" is not a valid value for the component \"" + _name + "\" (" + _type + ")");
        }
    }

    std::string Clock::getValue()
    {
        return tristateToString(getPin(1)->getPrevState());
    }

    Tristate Clock::getTristateValue()
    {
        return getPin(1)->getPrevState();
    }

} // namespace nts