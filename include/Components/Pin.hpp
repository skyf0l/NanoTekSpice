/*
** EPITECH PROJECT, 2021
** PIN
** File description:
** Pin header
*/

#ifndef PIN_H_
#define PIN_H_

#include <memory>
#include <list>
#include <unordered_map>

#include <Tristate.hpp>

#define ADD_PIN_IN(pin) _pins[pin] = std::unique_ptr<nts::Pin>(new Pin(nts::PIN_INPUT))
#define ADD_PIN_OUT(pin) _pins[pin] = std::unique_ptr<nts::Pin>(new Pin(nts::PIN_OUTPUT))
#define ADD_PIN_IO(pin) _pins[pin] = std::unique_ptr<nts::Pin>(new Pin(nts::PIN_IO))

namespace nts
{
    class IComponent;

    enum PinType
    {
        PIN_INPUT,
        PIN_OUTPUT,
        PIN_IO
    };
    struct Link
    {
        IComponent *component;
        std::size_t pin;
    };
    class Pin
    {
    public:
        Pin(PinType type);
        ~Pin();

        void connect(IComponent *linkTo, std::size_t linkToPin);
        void connect(std::unique_ptr<IComponent> &linkTo, std::size_t linkToPin);
        void disconnect(IComponent *linkTo, std::size_t linkToPin);
        void disconnect(std::unique_ptr<IComponent> &linkTo, std::size_t linkToPin);

        void compute();
        void simulateOutputComponents(std::size_t tick);
        void setState(Tristate state);
        void forceSetState(Tristate state);
        void setPrevState(Tristate prevState);

        // for PIN_INPUT
        void lock();
        void unlock();
        bool isLocked() const;

        PinType getType() const;
        Tristate getState() const;
        Tristate getPrevState() const;

        std::list<std::unique_ptr<Link>> &getConnectedTo();

    protected:
        PinType _type;
        bool _isLocked;

        std::size_t _tick;
        Tristate _state;
        Tristate _prevState;

        std::list<std::unique_ptr<Link>> _connectedTo;
    };
} // namespace nts

#endif /* !PIN_H_ */