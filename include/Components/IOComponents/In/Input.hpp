/*
** EPITECH PROJECT, 2021
** INPUT
** File description:
** Input header
*/

#ifndef INPUT_H_
#define INPUT_H_

#include <AComponent.hpp>

namespace nts
{
    class Input : public AComponent
    {
    public:
        Input(std::string name);
        ~Input() override;

        void simulate(std::size_t tick) override;

        void setValue(Tristate value) override;
        void setValue(std::string value) override;
        std::string getValue() override;
        Tristate getTristateValue() override;
    };
} // namespace nts

#endif /* !INPUT_H_ */