/*
** EPITECH PROJECT, 2021
** CLOCK
** File description:
** Clock header
*/

#ifndef CLOCK_H_
#define CLOCK_H_

#include <AComponent.hpp>

namespace nts
{
    class Clock : public AComponent
    {
    public:
        Clock(std::string name);
        ~Clock() override;

        void simulate(std::size_t tick) override;

        void setValue(Tristate value) override;
        void setValue(std::string value) override;
        std::string getValue() override;
        Tristate getTristateValue() override;

    protected:
        Tristate _nextState;
    };
} // namespace nts

#endif /* !CLOCK_H_ */