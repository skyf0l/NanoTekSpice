/*
** EPITECH PROJECT, 2021
** ICOMPONENT
** File description:
** IComponent header
*/

#ifndef ICOMPONENT_H_
#define ICOMPONENT_H_

#include <cstddef>
#include <memory>
#include <string>

#include <Tristate.hpp>
#include <Pin.hpp>

namespace nts
{
    enum ComponentType
    {
        INPUT,
        OUTPUT,
        LOGIC
    };
    class IComponent
    {
    public:
        virtual ~IComponent() = default;

        virtual void setValue(Tristate value) = 0;
        virtual void setValue(std::string value) = 0;
        virtual std::string getValue() = 0;
        virtual Tristate getTristateValue() = 0;

        virtual void simulate(std::size_t tick) = 0;
        virtual Tristate compute(std::size_t pin) = 0;
        virtual void setLink(std::size_t pin, std::unique_ptr<nts::IComponent> &other, std::size_t otherPin) = 0;

        virtual void dump(int offset) const = 0;

        virtual ComponentType getComponentType() const = 0;
        virtual const std::string &getType() const = 0;
        virtual const std::string &getName() const = 0;
        virtual const std::unique_ptr<Pin> &getPin(std::size_t pin) const = 0;
        virtual std::unordered_map<int, std::unique_ptr<nts::Pin>> &getPins() = 0;
    };
} // namespace nts

#endif /* !ICOMPONENT_H_ */