/*
** EPITECH PROJECT, 2021
** C2716
** File description:
** C2716 header (Read only memory (memory initialized for./rom.bin))
*/

#ifndef C2716_H_
#define C2716_H_

#include <AComponent.hpp>

namespace nts
{
    class C2716 : public AComponent
    {
    public:
        C2716(std::string name);
        ~C2716() override;

        void simulate(std::size_t tick) override;
        void setValue(std::string value) override;
        std::string getValue() override;

        void loadRom(std::string romPath = "./rom.bin");

    protected:
        std::string _romPath;
        char *_rom;

        static int nbPinIn;
        static int nbPinOut;
        static int pinInId[];
        static int pinOutId[];
    };
} // namespace nts

#endif /* !C2716_H_ */