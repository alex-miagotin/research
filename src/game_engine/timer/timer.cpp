#include "timer.hpp"

#include <SDL2/SDL.h>

Timer* Timer::m_instance = nullptr;

void Timer::tick()
{
    float currentTime = SDL_GetTicks();
    m_deltaTime = (currentTime - m_lastTime) * (TARGET_FPS / 1000.0f);
    if (m_deltaTime > TARGET_DELTA_TIME)
    {
        m_deltaTime = TARGET_DELTA_TIME;
    }
    
    m_lastTime = currentTime;
}