/*
** EPITECH PROJECT, 2021
** PIN
** File description:
** Pin class
*/

#include <IComponent.hpp>
#include <Pin.hpp>

namespace nts
{
    Pin::Pin(PinType type)
    {
        _type = type;
        _isLocked = false;

        _tick = 0;
        _state = UNDEFINED;
        _prevState = UNDEFINED;
    }

    Pin::~Pin()
    {
    }

    void Pin::connect(IComponent *linkTo, std::size_t linkToPin)
    {
        std::unique_ptr<Link> link = std::make_unique<Link>(Link{linkTo, linkToPin});
        link->component->getPin(link->pin)->lock();
        _connectedTo.push_back(std::move(link));
    }

    void Pin::connect(std::unique_ptr<IComponent> &linkTo, std::size_t linkToPin)
    {
        connect(linkTo.get(), linkToPin);
    }

    void Pin::disconnect(IComponent *linkTo, std::size_t linkToPin)
    {
        for (auto it = _connectedTo.begin(); it != _connectedTo.end(); it++)
            if (it->get()->component == linkTo && it->get()->pin == linkToPin)
            {
                _connectedTo.erase(it);
                break;
            }
    }

    void Pin::disconnect(std::unique_ptr<IComponent> &linkTo, std::size_t linkToPin)
    {
        disconnect(linkTo.get(), linkToPin);
    }

    void Pin::forceSetState(Tristate state)
    {
        _state = state;
    }

    void Pin::setState(Tristate state)
    {
        _state = state;
        for (auto it = _connectedTo.begin(); it != _connectedTo.end(); it++)
            it->get()->component->getPin(it->get()->pin)->setState(_state);
    }

    void Pin::setPrevState(Tristate prevState)
    {
        _prevState = prevState;
    }

    void Pin::compute()
    {
        _prevState = _state;
    }

    void Pin::simulateOutputComponents(std::size_t tick)
    {
        for (auto it = _connectedTo.begin(); it != _connectedTo.end(); it++)
            it->get()->component->simulate(tick);
    }

    void Pin::lock()
    {
        _isLocked = true;
    }

    void Pin::unlock()
    {
        _isLocked = false;
    }

    bool Pin::isLocked() const
    {
        return _isLocked;
    }

    PinType Pin::getType() const
    {
        return _type;
    }

    Tristate Pin::getState() const
    {
        return _state;
    }

    Tristate Pin::getPrevState() const
    {
        return _prevState;
    }

    std::list<std::unique_ptr<Link>> &Pin::getConnectedTo()
    {
        return _connectedTo;
    }

} // namespace nts