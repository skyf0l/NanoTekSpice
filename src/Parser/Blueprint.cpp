/*
** EPITECH PROJECT, 2021
** BLUEPRINT
** File description:
** Blueprint class
*/

#include <Blueprint.hpp>

namespace nts
{
    void Blueprint::loadBlueprint(std::unique_ptr<Circuit> &_circuit)
    {
        for (auto chipset = chipsets.begin(); chipset != chipsets.end(); chipset++)
            _circuit->addComponent(std::get<0>(*chipset), std::get<1>(*chipset));

        for (auto link = links.begin(); link != links.end(); link++)
            _circuit->addLink(std::get<0>(*link), std::get<1>(*link), std::get<2>(*link), std::get<3>(*link));

        for (auto circuit = circuits.begin(); circuit != circuits.end(); circuit++)
        {
            std::unique_ptr<nts::IComponent> &ioComponent = _circuit->getComponent(std::get<0>(*circuit));
            std::size_t pin = std::get<1>(*circuit);
            if (ioComponent->getType() == "input")
            {
                _circuit->getPins()[pin] = std::unique_ptr<nts::Pin>(new Pin(nts::PIN_INPUT));
                _circuit->getPins()[pin]->connect(ioComponent, 1);
            }
            else if (ioComponent->getType() == "output")
            {
                _circuit->getPins()[pin] = std::unique_ptr<nts::Pin>(new Pin(nts::PIN_OUTPUT));
                ioComponent->getPins()[1]->connect(_circuit.get(), pin);
            }
        }
        for (auto value = values.begin(); value != values.end(); value++)
            _circuit->setInput(std::get<0>(*value), std::get<1>(*value));

        // init roms
        for (auto cpn = _circuit->getComponents().begin(); cpn != _circuit->getComponents().end(); cpn++)
            if (cpn->second->getType() == "2716") // rom
                cpn->second->setValue(cpn->second->getValue());
        _circuit->simulate(0);
    }

} // namespace nts
