/*
** EPITECH PROJECT, 2021
** LOGGER
** File description:
** Logger class
*/

#include <fstream>
#include <math.h>
#include <Logger.hpp>

namespace nts
{
    Logger::Logger(std::string name) : AComponent("logger", name, OUTPUT)
    {
        for (int k = 1; k <= 8; k++)
            ADD_PIN_IN(k);
        ADD_PIN_IN(9);  // clock
        ADD_PIN_IN(10); // inhibit
        _value = "k";
        _logFilePath = "./log.bin";
        _hasPrint = false;
    }

    Logger::~Logger()
    {
    }

    void Logger::simulate(std::size_t tick)
    {
        AComponent::simulate(tick);

        char byte = 0;
        for (int k = 1; k <= 8; k++)
        {
            if (getPin(k)->getState() == UNDEFINED)
                return;
            byte += (getPin(k)->getState() == TRUE) ? std::pow(2, k - 1) : 0;
        }
        _value.clear();
        _value += byte;

        if (getPin(10)->getState() != FALSE)
            return;
        if (getPin(9)->getState() == UNDEFINED)
            return;
        if (getPin(9)->getState() == TRUE)
        {
            if (!_hasPrint)
            {
                std::ofstream logFile(_logFilePath, std::ios::out | std::ios::binary | std::ios::app);
                logFile.write(_value.c_str(), 1);
                _hasPrint = true;
            }
        }
        else if (getPin(9)->getState() == FALSE)
            _hasPrint = false;
    }

    void Logger::setValue(std::string value)
    {
        _logFilePath = value;
    }

    std::string Logger::getValue()
    {
        return _value;
    }

} // namespace nts