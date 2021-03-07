/*
** EPITECH PROJECT, 2021
** OUTPUT
** File description:
** Output header
*/

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <AComponent.hpp>

namespace nts
{
    class Output : public AComponent
    {
    public:
        Output(std::string name);
        ~Output() override;

        void simulate(std::size_t tick) override;

        std::string getValue() override;
    };
} // namespace nts

#endif /* !OUTPUT_H_ */