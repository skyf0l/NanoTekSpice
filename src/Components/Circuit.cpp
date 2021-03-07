/*
** EPITECH PROJECT, 2021
** CIRCUIT
** File description:
** Circuit class
*/

#include <regex>
#include <iostream>

#include <NtsException.hpp>
#include <ComponentFactory.hpp>
#include <Parser.hpp>
#include <Circuit.hpp>

namespace nts
{
    Circuit::Circuit() : AComponent("circuit")
    {
        _isComponent = false;
        _currentTick = 0;
    }

    Circuit::Circuit(const std::string &name, const std::string &type) : AComponent(type, name)
    {
        _isComponent = true;
        _currentTick = 0;
    }

    Circuit::~Circuit()
    {
    }

    void Circuit::simulate()
    {
        _currentTick++;
        simulate(_currentTick);
    }

    void Circuit::simulate(std::size_t tick)
    {
        for (auto it = _components.begin(); it != _components.end(); it++)
            if (it->second->getComponentType() == INPUT)
                it->second->simulate(tick);
        AComponent::simulate(tick);
    }

    Tristate Circuit::compute(std::size_t pin)
    {
        _pins[pin]->compute();
        return _pins[pin]->getState();
    }

    void Circuit::display()
    {
        std::cout << "tick: " << _currentTick << std::endl;

        std::cout << "input(s):" << std::endl;
        for (auto it = _components.begin(); it != _components.end(); it++)
            if (it->second->getType() == "input" || it->second->getType() == "clock")
                std::cout << "  " << it->second->getName() << ": " << it->second->getValue() << std::endl;

        std::cout << "output(s):" << std::endl;
        for (auto it = _components.begin(); it != _components.end(); it++)
            if (it->second->getType() == "output")
                std::cout << "  " << it->second->getName() << ": " << it->second->getValue() << std::endl;
    }

    void Circuit::dump(int offset) const
    {
        std::string padding;
        for (int k = 0; k < offset; k++)
            padding += "\t";

        AComponent::dump(offset);
        if (_components.size() > 0)
        {
            std::cout << padding << "chipsets:" << std::endl;
            for (auto it = _components.begin(); it != _components.end(); it++)
                it->second->dump(offset + 1);
        }
    }

    void Circuit::addComponent(std::string name, std::string type)
    {
        if (_components.find(name) != _components.end())
            throw InvalidComponentNameException("A component named \"" + name + "\" already exists");
        _components[name] = ComponentFactory::createComponent(type, name);
        if (_components[name] == nullptr)
            throw UnknownComponentException("Component type \"" + type + "\" not exists");
    }

    std::unique_ptr<nts::IComponent> &Circuit::getComponent(std::string name)
    {
        if (_components.find(name) == _components.end())
            throw InvalidComponentNameException("The component named \"" + name + "\" not exists");
        return _components[name];
    }

    void Circuit::removeComponent(std::string name)
    {
        if (_components.find(name) == _components.end())
            throw InvalidComponentNameException("The component named \"" + name + "\" not exists");
        _components.erase(name);
    }

    void Circuit::setRawInputs(char *const *inputs)
    {
        for (int k = 0; inputs[k]; k++)
            setRawInput(inputs[k]);
    }

    void Circuit::setRawInput(std::string input)
    {
        std::smatch matches;
        if (std::regex_search(input, matches, std::regex("^\\s*(\\S+)\\s*=\\s*(\\S+)\\s*$")))
        {
            std::string name = matches[1].str();
            std::string value = matches[2].str();
            setInput(name, value);
        }
        else
            throw InvalidInputCommandException("\"" + input + "\" is not a valid input command (name=value)");
    }

    void Circuit::setInput(std::string name, std::string value)
    {
        if (name == "*")
        {
            for (auto it = _components.begin(); it != _components.end(); it++)
                if (it->second->getType() == "input" || it->second->getType() == "clock")
                    it->second->setValue(value);
            return;
        }
        std::unique_ptr<nts::IComponent> &component = getComponent(name);
        component->setValue(value);
    }

    void Circuit::setInput(std::string name, Tristate value)
    {
        if (name == "*")
        {
            for (auto it = _components.begin(); it != _components.end(); it++)
                if (it->second->getType() == "input" || it->second->getType() == "clock")
                    it->second->setValue(value);
            return;
        }
        std::unique_ptr<nts::IComponent> &component = getComponent(name);
        component->setValue(value);
    }

    void Circuit::addLink(std::string name1, int pin1, std::string name2, int pin2)
    {
        std::unique_ptr<nts::IComponent> &component1 = getComponent(name1);
        std::unique_ptr<nts::IComponent> &component2 = getComponent(name2);
        try
        {
            component1->setLink(pin1, component2, pin2);
        }
        catch (InvalidPinException &ex)
        {
            component2->setLink(pin2, component1, pin1);
        }
    }

    bool Circuit::isComponent() const
    {
        return _isComponent;
    }

    std::map<std::string, std::unique_ptr<nts::IComponent>> &Circuit::getComponents()
    {
        return _components;
    }

    size_t Circuit::getCurrentTick() const
    {
        return _currentTick;
    }

} // namespace nts