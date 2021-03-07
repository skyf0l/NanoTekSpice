/*
** EPITECH PROJECT, 2021
** INPUT
** File description:
** Input class
*/

#include <NtsException.hpp>
#include <Input.hpp>

namespace nts
{
    Input::Input(std::string name) : AComponent("input", name, INPUT)
    {
        ADD_PIN_OUT(1);
    }

    Input::~Input()
    {
    }

    void Input::simulate(std::size_t tick)
    {
        AComponent::simulate(tick);
        compute(1);
    }

    void Input::setValue(Tristate value)
    {
        getPin(1)->setState(value);
    }

    void Input::setValue(std::string value)
    {
        try
        {
            getPin(1)->setState(stringToTristate(value));
        }
        catch (InvalidValueException &)
        {
            throw InvalidValueException("\"" + value + "\" is not a valid value for the component \"" + _name + "\" (" + _type + ")");
        }
    }

    std::string Input::getValue()
    {
        return tristateToString(getPin(1)->getPrevState());
    }

    Tristate Input::getTristateValue()
    {
        return getPin(1)->getPrevState();
    }

} // namespace nts