/*
** EPITECH PROJECT, 2021
** CIRCUIT
** File description:
** Circuit header
*/

#ifndef CIRCUIT_H_
#define CIRCUIT_H_

#include <map>

#include <AComponent.hpp>

namespace nts
{
    class Circuit : public AComponent
    {
    public:
        Circuit();
        Circuit(const std::string &name, const std::string &type);
        ~Circuit() override;

        void simulate();
        void display();

        void simulate(std::size_t tick) override;
        Tristate compute(std::size_t pin) override;
        void dump(int offset = 0) const override;

        void addComponent(std::string name, std::string type);
        std::unique_ptr<nts::IComponent> &getComponent(std::string name);
        void removeComponent(std::string name);
        void addLink(std::string name1, int pin1, std::string name2, int pin2);

        void setRawInputs(char *const *inputs);
        void setRawInput(std::string input);
        void setInput(std::string name, std::string value);
        void setInput(std::string name, Tristate value);

        bool isComponent() const;
        std::map<std::string, std::unique_ptr<nts::IComponent>> &getComponents();
        size_t getCurrentTick() const;

    protected:
        bool _isComponent;
        std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
    };
} // namespace nts

#endif /* !CIRCUIT_H_ */