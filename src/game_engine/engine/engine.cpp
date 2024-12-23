#include "engine.hpp"

#include "SDL2/SDL.h"

namespace engine {

Engine* Engine::m_instance = nullptr;

bool Engine::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    return m_isRunning = true;
}

bool Engine::cleanup() {
    return true;
}

void Engine::quit() {
    m_isRunning = false;
}

void Engine::update() {
    
}

void Engine::render() {
    
}

void Engine::events() {
    
}

} // namespace engine