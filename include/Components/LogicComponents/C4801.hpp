/*
** EPITECH PROJECT, 2021
** C4801
** File description:
** C4801 header (Random access memory)
*/

#ifndef C4801_H_
#define C4801_H_

#include <AComponent.hpp>

namespace nts
{
    class C4801 : public AComponent
    {
    public:
        C4801(std::string name);
        ~C4801() override;

        void simulate(std::size_t tick) override;

    protected:
        char *_ram;

        static int nbPinIn;
        static int nbPinIO;
        static int pinInId[];
        static int pinIOId[];
    };
} // namespace nts

#endif /* !C4801_H_ */