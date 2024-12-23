#include "engine.hpp"

namespace engine {

Engine* Engine::m_instance = nullptr;

bool Engine::init() {
    m_isRunning = true;
}

bool Engine::cleanup() {
    
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