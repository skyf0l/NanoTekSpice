/*
** EPITECH PROJECT, 2021
** FALSE
** File description:
** False class
*/

#include <False.hpp>

namespace nts
{
    False::False(std::string name) : AComponent("false", name, INPUT)
    {
        ADD_PIN_OUT(1);
    }

    False::~False()
    {
    }

    void False::simulate(std::size_t tick)
    {
        if (getPin(1)->getState() == UNDEFINED)
            getPin(1)->setState(FALSE);
        AComponent::simulate(tick);
        compute(1);
    }

    std::string False::getValue()
    {
        return tristateToString(FALSE);
    }

} // namespace nts