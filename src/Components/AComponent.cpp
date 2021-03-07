/*
** EPITECH PROJECT, 2021
** ACOMPONENT
** File description:
** AComponent class
*/

#include <iostream>
#include <memory>

#include <NtsException.hpp>
#include <AComponent.hpp>

namespace nts
{
    AComponent::AComponent(std::string type, std::string name, ComponentType componentType)
    {
        _type = type;
        _name = name;
        _componentType = componentType;
    }

    AComponent::~AComponent()
    {
    }

    void AComponent::simulate(std::size_t tick)
    {
        _currentTick = tick;
        for (auto it = _pins.begin(); it != _pins.end(); it++)
        {
            if (it->second->getState() != it->second->getPrevState())
            {
                it->second->compute();
                it->second->simulateOutputComponents(tick);
            }
        }
    }

    Tristate AComponent::compute(std::size_t pin)
    {
        _pins[pin]->compute();
        return _pins[pin]->getState();
    }

    void AComponent::setLink(std::size_t pin, std::unique_ptr<nts::IComponent> &other, std::size_t otherPin)
    {
        if (_pins.find(pin) == _pins.end())
            throw InvalidPinException("The component \"" + _name + "\" (" + _type + ") does not have pin number " + std::to_string(pin));

        const std::unique_ptr<nts::Pin> &pin1 = getPin(pin);
        const std::unique_ptr<nts::Pin> &pin2 = other->getPin(otherPin);
        if (pin1->getType() == pin2->getType())
            throw InvalidLinkException("Pin " + std::to_string(pin) + " of \"" + _name + "\" (" + _type + ") can not be connected to pin " + std::to_string(otherPin) + " of \"" + other->getName() + "\" (" + other->getType() + ") (IN to IN or OUT to OUT)");

        if (!(pin1->getType() == PIN_OUTPUT || pin2->getType() == PIN_INPUT))
            throw InvalidPinException("Pin " + std::to_string(pin) + " of \"" + _name + "\" (" + _type + ") is not an OUTPUT or " + std::to_string(otherPin) + " of \"" + other->getName() + "\" (" + other->getType() + ") is not an INPUT");

        if (pin2->isLocked())
            throw InvalidLinkException("Pin " + std::to_string(pin) + " of \"" + _name + "\" (" + _type + ") can not be connected to pin " + std::to_string(otherPin) + " of \"" + other->getName() + "\" (" + other->getType() + ") (IN is already linked to another component)");
        pin1->connect(other, otherPin);
    }

    void AComponent::dump(int offset) const
    {
        if (_type == "input" || _type == "output")
            return;

        std::string padding;
        for (int k = 0; k < offset; k++)
            padding += "\t";
        std::cout << padding << "-> " << _type << (_name.empty() ? "" : " (name: " + _name + ")") << std::endl;
    }

    void AComponent::setValue(Tristate)
    {
        throw UnusedMethodException("Function \"setValue\" is not supposed to be called by the component \"" + _name + "\" (" + _type + ")");
    }

    void AComponent::setValue(std::string)
    {
        throw UnusedMethodException("Function \"setValue\" is not supposed to be called by the component \"" + _name + "\" (" + _type + ")");
    }

    std::string AComponent::getValue()
    {
        throw UnusedMethodException("Function \"getValue\" is not supposed to be called by the component \"" + _name + "\" (" + _type + ")");
    }

    Tristate AComponent::getTristateValue()
    {
        throw UnusedMethodException("Function \"getValue\" is not supposed to be called by the component \"" + _name + "\" (" + _type + ")");
    }

    ComponentType AComponent::getComponentType() const
    {
        return _componentType;
    }

    const std::string &AComponent::getType() const
    {
        return _type;
    }

    const std::string &AComponent::getName() const
    {
        return _name;
    }

    const std::unique_ptr<Pin> &AComponent::getPin(std::size_t pin) const
    {
        if (_pins.find(pin) == _pins.end())
            throw InvalidPinException("The component \"" + _type + "\" does not have pin number " + std::to_string(pin));
        return _pins.find(pin)->second;
    }

    std::unordered_map<int, std::unique_ptr<nts::Pin>> &AComponent::getPins()
    {
        return _pins;
    }

} // namespace nts