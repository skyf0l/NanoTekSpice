/*
** EPITECH PROJECT, 2021
** TRISTATE_CORE
** File description:
** Tristate_core class
*/

#include <Tristate_core.hpp>

namespace nts
{
    Tristate_core::Tristate_core(std::string name) : AComponent("tristate_core", name)
    {
        ADD_PIN_IN(1);  // in
        ADD_PIN_IN(2);  // enable
        ADD_PIN_OUT(3); // out
    }

    Tristate_core::~Tristate_core()
    {
    }

    void Tristate_core::simulate(std::size_t tick)
    {
        if (getPin(2)->getState() == TRUE)
            _pins[3]->setState(getPin(1)->getState());
        else
            _pins[3]->setState(UNDEFINED);
        AComponent::simulate(tick);
    }

} // namespace nts