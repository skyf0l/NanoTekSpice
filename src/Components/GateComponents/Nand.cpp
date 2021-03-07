/*
** EPITECH PROJECT, 2021
** NAND
** File description:
** Nand class
*/

#include <Nand.hpp>

namespace nts
{
    Nand::Nand(std::string name) : AComponent("nand", name)
    {
        ADD_PIN_IN(1);  // in_1
        ADD_PIN_IN(2);  // in_2
        ADD_PIN_OUT(3); // out
    }

    Nand::~Nand()
    {
    }

    void Nand::simulate(std::size_t tick)
    {
        _pins[3]->setState(!(compute(1) && compute(2)));
        AComponent::simulate(tick);
        compute(3);
    }

} // namespace nts