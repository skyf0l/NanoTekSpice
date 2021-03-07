/*
** EPITECH PROJECT, 2021
** TRUE
** File description:
** True class
*/

#include <True.hpp>

namespace nts
{
    True::True(std::string name) : AComponent("true", name, INPUT)
    {
        ADD_PIN_OUT(1);
    }

    True::~True()
    {
    }

    void True::simulate(std::size_t tick)
    {
        if (getPin(1)->getState() == UNDEFINED)
            getPin(1)->setState(TRUE);
        AComponent::simulate(tick);
        compute(1);
    }

    std::string True::getValue()
    {
        return tristateToString(TRUE);
    }

} // namespace nts