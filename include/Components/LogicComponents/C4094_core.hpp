/*
** EPITECH PROJECT, 2021
** C4094_CORE
** File description:
** C4094_core header (8 bits shift register)
*/

#ifndef C4094_CORE_H_
#define C4094_CORE_H_

#include <vector>

#include <AComponent.hpp>

namespace nts
{
    class C4094_core : public AComponent
    {
    public:
        C4094_core(std::string name);
        ~C4094_core() override;

        void simulate(std::size_t tick) override;

    protected:
        Tristate _lastClockState;
        std::vector<Tristate> _data;

        static int nbPinOut;
        static int pinOutId[];
    };
} // namespace nts

#endif /* !C4094_CORE_H_ */