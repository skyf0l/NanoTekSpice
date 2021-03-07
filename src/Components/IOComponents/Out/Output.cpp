/*
** EPITECH PROJECT, 2021
** OUTPUT
** File description:
** Output class
*/

#include <Output.hpp>

namespace nts
{
    Output::Output(std::string name) : AComponent("output", name, OUTPUT)
    {
        ADD_PIN_IN(1);
    }

    Output::~Output()
    {
    }

    void Output::simulate(std::size_t tick)
    {
        AComponent::simulate(tick);
        compute(1);
    }

    std::string Output::getValue()
    {
        return tristateToString(getPin(1)->getPrevState());
    }

} // namespace nts