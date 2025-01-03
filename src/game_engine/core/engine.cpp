#include "engine.hpp"

#include "../graphics/texture_manager.hpp"
#include "../characters/monster.hpp"
#include "../inputs/input.hpp"
#include "../timer/timer.hpp"

#include "../map/map_parser.hpp"

namespace core {

Engine* Engine::m_instance = nullptr;
Monster* player = nullptr;

bool Engine::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if (m_window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 1);

    if(!map::MapParser::getInstance()->load()) {
        SDL_Log("Failed to load map");
        return false;
    }
    m_levelMap = map::MapParser::getInstance()->getMap("map1");

    graphics::TextureManager::getInstance()->load("player", "/characters/monsters/owlet_sprite.png");
    player = new Monster({10, 10, 32, 32, "player", SDL_FLIP_NONE});

    return m_isRunning = true;
}

bool Engine::cleanup() {
    graphics::TextureManager::getInstance()->clean();

    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    SDL_Log("Game Cleaned");
    
    return true;
}

void Engine::quit() {
    m_isRunning = false;
}

void Engine::update() {
    float dt = Timer::getInstance()->getDeltaTime();
    player->update(dt);
}

void Engine::render() {
    SDL_RenderClear(m_renderer);

    m_levelMap->render();

    player->render();

    SDL_RenderPresent(m_renderer);
}

void Engine::events() {
    Input::getInstance()->listen();
}

} // namespace core