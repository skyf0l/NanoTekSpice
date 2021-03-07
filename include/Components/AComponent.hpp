/*
** EPITECH PROJECT, 2021
** COMPONENT
** File description:
** AComponent header
*/

#ifndef ACOMPONENT_H_
#define ACOMPONENT_H_

#include <unordered_map>

#include <NtsException.hpp>
#include <IComponent.hpp>

namespace nts
{
    class AComponent : public IComponent
    {
    public:
        AComponent(std::string type, std::string name = "", ComponentType componentType = LOGIC);
        virtual ~AComponent() override;

        void simulate(std::size_t tick) override;
        Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, std::unique_ptr<nts::IComponent> &other, std::size_t otherPin) override;
        void dump(int offset = 0) const override;

        virtual void setValue(Tristate value) override;
        virtual void setValue(std::string value) override;
        virtual std::string getValue() override;
        virtual Tristate getTristateValue() override;

        ComponentType getComponentType() const override;
        const std::string &getType() const override;
        const std::string &getName() const override;
        const std::unique_ptr<Pin> &getPin(std::size_t pin) const override;
        std::unordered_map<int, std::unique_ptr<nts::Pin>> &getPins() override;

    protected:
        ComponentType _componentType;
        std::string _type;
        std::string _name;

        std::unordered_map<int, std::unique_ptr<nts::Pin>> _pins;
        size_t _currentTick;
    };
} // namespace nts

#endif /* !COMPONENT_H_ */