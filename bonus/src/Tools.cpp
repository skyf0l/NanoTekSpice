/*
** EPITECH PROJECT, 2021
** TOOLS
** File description:
** Tools class
*/

#include <Tools.hpp>

namespace nts
{
    FPS::FPS(float nbPlots)
    {
        _nbPlots = nbPlots;
        _lastTime = _clock.getElapsedTime().asSeconds();
    }

    FPS::~FPS()
    {
    }

    void FPS::reset()
    {
        _fpsPlots.clear();
        _clock.restart();
        _lastTime = _clock.getElapsedTime().asSeconds();
    }

    int FPS::getFPS()
    {
        float elapsedTime = _clock.getElapsedTime().asSeconds() - _lastTime;
        float fps = 1.0 / elapsedTime;
        _lastTime = _clock.getElapsedTime().asSeconds();

        _fpsPlots.push_back(fps);
        while (_fpsPlots.size() > _nbPlots)
            _fpsPlots.pop_front();

        float medFps = 0;
        for (auto it = _fpsPlots.begin(); it != _fpsPlots.end(); it++)
            medFps += *it;
        medFps /= _fpsPlots.size();
        return (int)medFps;
    }

} // namespace nts