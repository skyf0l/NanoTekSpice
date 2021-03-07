/*
** EPITECH PROJECT, 2021
** FALSE
** File description:
** False header
*/

#ifndef FALSE_H_
#define FALSE_H_

#include <AComponent.hpp>

namespace nts
{
    class False : public AComponent
    {
    public:
        False(std::string name);
        ~False() override;

        void simulate(std::size_t tick) override;

        std::string getValue() override;
    };
} // namespace nts

#endif /* !FALSE_H_ */