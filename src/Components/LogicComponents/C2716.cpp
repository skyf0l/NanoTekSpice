/*
** EPITECH PROJECT, 2021
** C2716
** File description:
** C2716 class (Read only memory (memory initialized for./rom.bin))
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#ifndef _WIN32
#include <sys/stat.h>
#endif

#include <C2716.hpp>

#define ENABLE_PIN 18
#define READ_PIN 20

namespace nts
{
    int C2716::nbPinIn = 11;
    int C2716::nbPinOut = 8;
    int C2716::pinInId[11] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19};
    int C2716::pinOutId[8] = {9, 10, 11, 13, 14, 15, 16, 17};

    C2716::C2716(std::string name) : AComponent("2716", name)
    {
        ADD_PIN_IN(ENABLE_PIN); // enable
        ADD_PIN_IN(READ_PIN);   // read
        for (int in = 0; in < nbPinIn; in++)
            ADD_PIN_IN(pinInId[in]); // addr_n
        for (int out = 0; out < nbPinOut; out++)
            ADD_PIN_OUT(pinOutId[out]); // out_n

        _rom = nullptr;
        _romPath = "./rom.bin";
    }

    C2716::~C2716()
    {
        if (_rom)
            delete[] _rom;
    }

    void C2716::simulate(std::size_t tick)
    {
        // init rom
        if (_rom == nullptr)
            loadRom();

        // read addr
        int addr = 0;
        for (int in = 0; in < nbPinIn; in++)
        {
            Tristate pinValue = getPin(pinInId[in])->getState();
            if (pinValue == TRUE)
                addr += std::pow(2, in);
            else if (pinValue == UNDEFINED)
            {
                addr = -1;
                break;
            }
        }
        if (addr == -1 || getPin(ENABLE_PIN)->getState() == TRUE || getPin(READ_PIN)->getState() == TRUE)
        {
            // write undefined
            for (int out = 0; out < nbPinOut; out++)
                getPin(pinOutId[out])->setState(UNDEFINED);
        }
        else
        {
            char byte = _rom[addr];

            // write readed byte
            for (int out = 0; out < nbPinOut; out++)
            {
                if (byte >> out & 0b1)
                    getPin(pinOutId[out])->setState(TRUE);
                else
                    getPin(pinOutId[out])->setState(FALSE);
            }
        }

        AComponent::simulate(tick);
    }

    void C2716::setValue(std::string value)
    {
        loadRom(value);

        // update outputs
        if (_rom)
            simulate(_currentTick);
    }

    std::string C2716::getValue()
    {
        return (_romPath);
    }

    void C2716::loadRom(std::string romPath)
    {
        if (_rom == nullptr)
            _rom = new char[2048 * 8];

        _romPath = romPath;
        memset(_rom, 0, 2048 * 8);

        // check if file is readable (only Linux)
#ifndef _WIN32
        struct stat fileStat;
        stat(romPath.c_str(), &fileStat);
        if (!S_ISREG(fileStat.st_mode))
            throw InvalidRomFileException("Can not open rom file, not a regular file: " + _romPath);
#endif

        std::ifstream romFile(_romPath, std::fstream::in);
        if (!romFile.is_open())
            throw InvalidRomFileException("Can not open rom file: " + _romPath);

        romFile.read(_rom, 2048 * 8);
        if (romFile.gcount() == -1)
            throw InvalidRomFileException("An error occurred while reading rom file: " + _romPath);
        romFile.close();
    }

} // namespace nts