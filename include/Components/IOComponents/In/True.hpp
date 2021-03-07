/*
** EPITECH PROJECT, 2021
** TRUE
** File description:
** True header
*/

#ifndef TRUE_H_
#define TRUE_H_

#include <AComponent.hpp>

namespace nts
{
    class True : public AComponent
    {
    public:
        True(std::string name);
        ~True() override;

        void simulate(std::size_t tick) override;

        std::string getValue() override;
    };
} // namespace nts

#endif /* !TRUE_H_ */