/*
** EPITECH PROJECT, 2021
** GRAPHICSHELL
** File description:
** GraphicShell class
*/

#include <iostream>
#include <iomanip>
#include <thread>

#include <Tristate.hpp>
#include <Parser.hpp>
#include <Tools.hpp>

#include <GraphicShell.hpp>

namespace nts
{
    GraphicShell::GraphicShell(std::string path, char *const *raw_inputs)
    {
        // init circuit
        _circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(path, _circuit);
        if (raw_inputs)
            _circuit->setRawInputs(raw_inputs);
        _title = Parser::getFileName(path);

        // extract in and out pins
        for (auto compnent = _circuit->getComponents().begin(); compnent != _circuit->getComponents().end(); compnent++)
        {
            if (compnent->second->getType() == "input" || compnent->second->getType() == "clock")
                _inputs.push_back(compnent->second.get());
            else if (compnent->second->getType() == "output")
                _outputs.push_back(compnent->second.get());
        }
        // sort pins
        sort(_inputs.begin(), _inputs.end(), [](const IComponent *a, const IComponent *b) -> bool { return a->getName() < b->getName(); });
        sort(_outputs.begin(), _outputs.end(), [](const IComponent *a, const IComponent *b) -> bool { return a->getName() < b->getName(); });

        // init window
        _width = 1280;
        _height = 720;
        _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(_width, _height), "NanoTekSpice"); // abort if window can not open
        _window->setFramerateLimit(100);

        // init _font
        if (!_font.loadFromFile("assets/fonts/Roboto-Black.ttf"))
            throw AssetLoadingException("Can not load font: assets/fonts/Roboto-Black.ttf");

        // init _text
        _text.setFont(_font);
        _text.setFillColor(sf::Color::White);

        // shapes
        _ioCircleRadius = 18;
        _circuitLeftShift = _width * 0.2;
        _UIRightShift = _width * 0.3;

        // simulation
        _simulateAtEachPinUpdate = false;
        _loopSimulate = false;
        _loopDelay = 0.25;
        _lastLoop = _loopClock.getElapsedTime().asSeconds();
    }

    GraphicShell::~GraphicShell()
    {
    }

    IComponent *GraphicShell::getInputClicked(int mouseX, int mouseY)
    {
        for (int in = 0; in < _inputs.size(); in++)
        {
            float x = _width * .35 - _circuitLeftShift;
            float y = _height * .9 * (in + .5) / _inputs.size() + _height * .05;

            _circleShape.setRadius(_ioCircleRadius);
            _circleShape.setPosition(sf::Vector2f(x, y - _ioCircleRadius));
            if (_circleShape.getGlobalBounds().contains(mouseX, mouseY))
                return _inputs[in];
        }
        return nullptr;
    }

    void GraphicShell::handleEvents(sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonPressed && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)))
        {
            // fix mouse pos (for resize)
            int mouseX = sf::Mouse::getPosition(*_window).x * _width / (float)_window->getSize().x;
            int mouseY = sf::Mouse::getPosition(*_window).y * _height / (float)_window->getSize().y;

            // inputs
            IComponent *clickedInput = getInputClicked(mouseX, mouseY);
            if (clickedInput)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (clickedInput->getPin(1)->getState() == UNDEFINED)
                        _circuit->setInput(clickedInput->getName(), FALSE);
                    else
                        _circuit->setInput(clickedInput->getName(), !clickedInput->getPin(1)->getState());
                }
                else
                    _circuit->setInput(clickedInput->getName(), UNDEFINED);
                if (_simulateAtEachPinUpdate)
                    _circuit->simulate();
            }

            // simulate button
            _rectangleShape.setSize(sf::Vector2f(_width * .25, _height * .18));
            _rectangleShape.setPosition(sf::Vector2f(
                (_width - _rectangleShape.getGlobalBounds().width) / 2 + _UIRightShift,
                _height * 0.1));
            if (_rectangleShape.getGlobalBounds().contains(mouseX, mouseY))
                _circuit->simulate();

            // each pin update simulation button
            _rectangleShape.setSize(sf::Vector2f(_width * .25, _height * .18));
            _rectangleShape.setPosition(sf::Vector2f(
                (_width - _rectangleShape.getGlobalBounds().width) / 2 + _UIRightShift,
                _height * 0.3));
            if (_rectangleShape.getGlobalBounds().contains(mouseX, mouseY))
            {
                _simulateAtEachPinUpdate = !_simulateAtEachPinUpdate;
                if (_simulateAtEachPinUpdate)
                    _loopSimulate = false;
            }

            // loop simulate button
            _rectangleShape.setSize(sf::Vector2f(_width * .25, _height * .18));
            _rectangleShape.setPosition(sf::Vector2f(
                (_width - _rectangleShape.getGlobalBounds().width) / 2 + _UIRightShift,
                _height * 0.5));
            if (_rectangleShape.getGlobalBounds().contains(mouseX, mouseY))
            {
                _loopSimulate = !_loopSimulate;
                _lastLoop = _loopClock.getElapsedTime().asSeconds();
                if (_loopSimulate)
                    _simulateAtEachPinUpdate = false;
            }

            // draw slow down loop simulation button
            _rectangleShape.setSize(sf::Vector2f(_width * .25 * .48, _height * .18));
            _rectangleShape.setPosition(sf::Vector2f(
                (_width * .75) / 2 + _UIRightShift,
                _height * 0.7));
            if (_rectangleShape.getGlobalBounds().contains(mouseX, mouseY))
                _loopDelay *= 2;

            // draw speed up loop simulation button
            _rectangleShape.setSize(sf::Vector2f(_width * .25 * .48, _height * .18));
            _rectangleShape.setPosition(sf::Vector2f(
                (_width * 1.01) / 2 + _UIRightShift,
                _height * 0.7));
            if (_rectangleShape.getGlobalBounds().contains(mouseX, mouseY))
                _loopDelay /= 2;
        }
    }

    void GraphicShell::loopUpdate()
    {
        while (_window->isOpen())
            update();
    }

    void GraphicShell::update()
    {
        while (_window->isOpen() && _loopSimulate && _loopClock.getElapsedTime().asSeconds() - _lastLoop > _loopDelay)
        {
            _lastLoop += _loopDelay;
            _circuit->simulate();
        }
    }

    void GraphicShell::display()
    {
        _window->clear(sf::Color(0x323232ff));
        _text.setCharacterSize(24);

        // display tick
        _text.setString("Tick: " + std::to_string(_circuit->getCurrentTick()));
        _text.setPosition(sf::Vector2f((_width - _text.getGlobalBounds().width) / 2 + _UIRightShift, _height * 0.05));
        _window->draw(_text);

        _text.setCharacterSize(20);

        // draw simulate button
        _rectangleShape.setFillColor(sf::Color(122));
        _rectangleShape.setSize(sf::Vector2f(_width * .25, _height * .18));
        _rectangleShape.setPosition(sf::Vector2f(
            (_width - _rectangleShape.getGlobalBounds().width) / 2 + _UIRightShift,
            _height * 0.1));
        _window->draw(_rectangleShape);
        _text.setString("Simulate");
        _text.setPosition(sf::Vector2f(
            _rectangleShape.getGlobalBounds().left + (_rectangleShape.getGlobalBounds().width - _text.getGlobalBounds().width) / 2,
            _rectangleShape.getGlobalBounds().top + (_rectangleShape.getGlobalBounds().height - _text.getGlobalBounds().height) / 2));
        _window->draw(_text);

        // draw each pin update simulation button
        _rectangleShape.setFillColor(sf::Color(122));
        _rectangleShape.setSize(sf::Vector2f(_width * .25, _height * .18));
        _rectangleShape.setPosition(sf::Vector2f(
            (_width - _rectangleShape.getGlobalBounds().width) / 2 + _UIRightShift,
            _height * 0.3));
        _window->draw(_rectangleShape);
        if (_simulateAtEachPinUpdate)
            _text.setString("Simulate at each pin update");
        else
            _text.setString("Not simulate at each pin update");
        _text.setPosition(sf::Vector2f(
            _rectangleShape.getGlobalBounds().left + (_rectangleShape.getGlobalBounds().width - _text.getGlobalBounds().width) / 2,
            _rectangleShape.getGlobalBounds().top + (_rectangleShape.getGlobalBounds().height - _text.getGlobalBounds().height) / 2));
        _window->draw(_text);

        // draw loop simulation button
        _rectangleShape.setFillColor(sf::Color(122));
        _rectangleShape.setSize(sf::Vector2f(_width * .25, _height * .18));
        _rectangleShape.setPosition(sf::Vector2f(
            (_width - _rectangleShape.getGlobalBounds().width) / 2 + _UIRightShift,
            _height * 0.5));
        _window->draw(_rectangleShape);

        std::stringstream stream;
        stream << std::fixed << std::setprecision(5) << (1.0 / _loopDelay);
        std::string loopPerSecond = stream.str();
        loopPerSecond.erase(loopPerSecond.find_last_not_of('0') + 1);
        loopPerSecond.erase(loopPerSecond.find_last_not_of('.') + 1);

        if (_loopSimulate)
            _text.setString("Loop (" + loopPerSecond + " simulation/s)");
        else
            _text.setString("Not loop (" + loopPerSecond + " simulation/s)");
        _text.setPosition(sf::Vector2f(
            _rectangleShape.getGlobalBounds().left + (_rectangleShape.getGlobalBounds().width - _text.getGlobalBounds().width) / 2,
            _rectangleShape.getGlobalBounds().top + (_rectangleShape.getGlobalBounds().height - _text.getGlobalBounds().height) / 2));
        _window->draw(_text);

        // draw slow down loop simulation button
        _rectangleShape.setFillColor(sf::Color(122));
        _rectangleShape.setSize(sf::Vector2f(_width * .25 * .48, _height * .18));
        _rectangleShape.setPosition(sf::Vector2f(
            (_width * .75) / 2 + _UIRightShift,
            _height * 0.7));
        _window->draw(_rectangleShape);
        _text.setString("Slow down");
        _text.setPosition(sf::Vector2f(
            _rectangleShape.getGlobalBounds().left + (_rectangleShape.getGlobalBounds().width - _text.getGlobalBounds().width) / 2,
            _rectangleShape.getGlobalBounds().top + (_rectangleShape.getGlobalBounds().height - _text.getGlobalBounds().height) / 2));
        _window->draw(_text);

        // draw speed up loop simulation button
        _rectangleShape.setFillColor(sf::Color(122));
        _rectangleShape.setSize(sf::Vector2f(_width * .25 * .48, _height * .18));
        _rectangleShape.setPosition(sf::Vector2f(
            (_width * 1.01) / 2 + _UIRightShift,
            _height * 0.7));
        _window->draw(_rectangleShape);
        _text.setString("Speed up");
        _text.setPosition(sf::Vector2f(
            _rectangleShape.getGlobalBounds().left + (_rectangleShape.getGlobalBounds().width - _text.getGlobalBounds().width) / 2,
            _rectangleShape.getGlobalBounds().top + (_rectangleShape.getGlobalBounds().height - _text.getGlobalBounds().height) / 2));
        _window->draw(_text);

        // draw component
        _rectangleShape.setFillColor(sf::Color(122));
        _rectangleShape.setSize(sf::Vector2f(_width * .27, _height * .9));
        _rectangleShape.setPosition(sf::Vector2f(
            (_width - _rectangleShape.getGlobalBounds().width) / 2 - _circuitLeftShift,
            (_height - _rectangleShape.getGlobalBounds().height) / 2));
        _window->draw(_rectangleShape);

        // draw component name
        _text.setString(_title);
        _text.setPosition(sf::Vector2f((_width - _text.getGlobalBounds().width) / 2 - _circuitLeftShift, (_height - _text.getCharacterSize()) / 2));
        _window->draw(_text);

        // draw input and output pins
        _text.setCharacterSize(_ioCircleRadius);
        for (int in = 0; in < _inputs.size(); in++)
        {
            float x = _width * .35 - _circuitLeftShift;
            float y = _height * .9 * (in + .5) / _inputs.size() + _height * .05;

            // draw input pin
            _circleShape.setRadius(_ioCircleRadius);
            _circleShape.setFillColor(tristateToColor(_inputs[in]->getPin(1)->getState()));
            _circleShape.setPosition(sf::Vector2f(x, y - _ioCircleRadius));
            _window->draw(_circleShape);

            // draw text
            _text.setString(_inputs[in]->getName());
            _text.setPosition(sf::Vector2f(x - _ioCircleRadius * 2 - _text.getLocalBounds().width, y - _text.getCharacterSize() / 2));
            _window->draw(_text);
        }

        for (int out = 0; out < _outputs.size(); out++)
        {
            float x = _width * .65 - _circuitLeftShift;
            float y = _height * .9 * (out + .5) / _outputs.size() + _height * .05;

            // draw output pin
            _circleShape.setRadius(_ioCircleRadius);
            _circleShape.setFillColor(tristateToColor(stringToTristate(_outputs[out]->getValue())));
            _circleShape.setPosition(sf::Vector2f(x - _ioCircleRadius * 2, y - _ioCircleRadius));
            _window->draw(_circleShape);

            // draw text
            _text.setString(_outputs[out]->getName());
            _text.setPosition(sf::Vector2f(x + _ioCircleRadius * 2, y - _text.getCharacterSize() / 2));
            _window->draw(_text);
        }

        _window->display();
    }

    int GraphicShell::run()
    {
        sf::Event event;
        FPS fps;

        std::thread updateThread(&GraphicShell::loopUpdate, this);
        while (_window->isOpen())
        {
            while (_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    _window->close();
                handleEvents(event);
            }
            display();
            _window->setTitle("NanoTekSpice: " + _title + " (" + std::to_string(fps.getFPS()) + " fps)");
        }
        updateThread.join();
        return EXIT_SUCCESS;
    }

} // namespace nts
