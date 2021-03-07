/*
** EPITECH PROJECT, 2021
** GRAPHICSHELL
** File description:
** GraphicShell header
*/

#ifndef GRAPHICSHELL_H_
#define GRAPHICSHELL_H_

#include <SFML/Graphics.hpp>

#include <IShell.hpp>
#include <Circuit.hpp>

namespace nts
{
    class GraphicShell : public IShell
    {
    public:
        GraphicShell(std::string path, char *const *raw_inputs);
        ~GraphicShell() override;

        int run() override;

        IComponent *getInputClicked(int x, int y);

        void handleEvents(sf::Event &event);
        void update();
        void loopUpdate();
        void display();

    protected:
        std::unique_ptr<sf::RenderWindow> _window;
        int _width;
        int _height;
        float _circuitLeftShift;
        float _UIRightShift;

        std::string _title;
        std::unique_ptr<Circuit> _circuit;
        std::vector<IComponent *> _inputs;
        std::vector<IComponent *> _outputs;

        sf::Font _font;
        sf::Text _text;

        sf::CircleShape _circleShape;
        int _ioCircleRadius;
        sf::RectangleShape _rectangleShape;

        // simulation
        bool _simulateAtEachPinUpdate;
        bool _loopSimulate;
        sf::Clock _loopClock;
        double _loopDelay;
        float _lastLoop;

    };
} // namespace nts

#endif /* !GRAPHICSHELL_H_ */