/*
** EPITECH PROJECT, 2021
** TRISTATE_CORE
** File description:
** Tristate_core header
*/

#ifndef TRISTATE_CORE_H_
#define TRISTATE_CORE_H_

#include <AComponent.hpp>

namespace nts
{
    class Tristate_core : public AComponent
    {
    public:
        Tristate_core(std::string name);
        ~Tristate_core() override;

        void simulate(std::size_t tick) override;
    };
} // namespace nts

#endif /* !TRISTATE_CORE_H_ */