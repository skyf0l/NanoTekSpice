/*
** EPITECH PROJECT, 2021
** TOOLS
** File description:
** Tools header
*/

#ifndef TOOLS_H_
#define TOOLS_H_

#include <list>
#include <SFML/Graphics.hpp>

namespace nts
{
    class FPS
    {
    public:
        FPS(float nbPlots = 100);
        ~FPS();

        void reset();
        int getFPS();

    protected:
        int _nbPlots;
        std::list<float> _fpsPlots;

        sf::Clock _clock;
        float _lastTime;
    };
} // namespace nts

#endif /* !TOOLS_H_ */