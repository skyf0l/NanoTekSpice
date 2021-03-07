/*
** EPITECH PROJECT, 2021
** C4040_CORE
** File description:
** C4040_CORE header (12 bits counter)
*/

#ifndef C4040_CORE_H_
#define C4040_CORE_H_

#include <AComponent.hpp>

namespace nts
{
    class C4040_core : public AComponent
    {
    public:
        C4040_core(std::string name);
        ~C4040_core() override;

        void simulate(std::size_t tick) override;

    protected:
        int _count;
        Tristate _lastClockState;

        static int nbPinOut;
        static int pinOutId[];
    };
} // namespace nts

#endif /* !C4040_CORE_H_ */