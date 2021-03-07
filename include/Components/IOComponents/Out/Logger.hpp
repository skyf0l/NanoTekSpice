/*
** EPITECH PROJECT, 2021
** LOGGER
** File description:
** Logger header
*/

#ifndef LOGGER_H_
#define LOGGER_H_

#include <AComponent.hpp>

namespace nts
{
    class Logger : public AComponent
    {
    public:
        Logger(std::string name);
        ~Logger() override;

        void simulate(std::size_t tick) override;

        void setValue(std::string value);
        std::string getValue() override;

    protected:
        std::string _logFilePath;
        std::string _value;
        bool _hasPrint;
    };
} // namespace nts

#endif /* !LOGGER_H_ */