/*
** EPITECH PROJECT, 2021
** NAND
** File description:
** Nand header
*/

#ifndef NAND_H_
#define NAND_H_

#include <AComponent.hpp>

namespace nts
{
    class Nand : public AComponent
    {
    public:
        Nand(std::string name);
        ~Nand() override;

        void simulate(std::size_t tick) override;
    };
} // namespace nts

#endif /* !NAND_H_ */