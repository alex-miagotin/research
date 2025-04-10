#include "engine.hpp"

#include "../graphics/texture_manager.hpp"
#include "../characters/monster.hpp"
#include "../inputs/input.hpp"
#include "../timer/timer.hpp"
#include "../camera/camera.hpp"

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

    std::string mapName = "map1";
    if(!map::MapParser::getInstance()->load(mapName, "/maps/map1.tmx")) {
        SDL_Log("Failed to load map");
        return false;
    }
    m_levelMap = map::MapParser::getInstance()->getMap(mapName);

    if (m_levelMap == nullptr) {
        SDL_Log("Failed to get map");
        return false;
    }

    graphics::TextureManager::getInstance()->load("bg1", "/background/1.jpg");
    graphics::TextureManager::getInstance()->load("player", "/characters/monsters/owlet_sprite.png");
    player = new Monster({10, 10, 32, 32, "player", SDL_FLIP_NONE});
    
    game_engine::Camera::getInstance()->setTarget(player->getTransform()->getPosition());

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

    auto lastPlayerPositionX = player->getTransform()->getPosition()->x;
    auto lastPlayerPositionY = player->getTransform()->getPosition()->y;

    player->update(dt);
    m_levelMap->update();


    auto collisionLayer = reinterpret_cast<map::TileLayer *>(m_levelMap->getLayers().back());
    auto playerPosition = player->getTransform()->getPosition();
    auto playerWidth = player->getWidth();
    auto playerHeight = player->getHeight();

    // if (playerPosition->x < 0) {
    //     player->getTransform()->setPosition({0, playerPosition->y});
    // }
    // if (playerPosition->x + playerWidth >= game_engine::Camera::getInstance()->getViewBox().w) {
    //     player->getTransform()->setPosition({lastPlayerPositionX, playerPosition->y});
    // }

    // if (playerPosition->y < 0) {
    //     player->getTransform()->setPosition({playerPosition->x, 0});
    // }
    if (playerPosition->y + playerHeight >= game_engine::Camera::getInstance()->getViewBox().h) {
        player->getTransform()->setPosition({playerPosition->x, (float)game_engine::Camera::getInstance()->getViewBox().h - playerHeight});
    }

    // for(auto tile: collisionLayer->getTiles())
    // {
    //     if (playerPosition->x + playerWidth >= tile.x && playerPosition->x <= tile.x + tile.width && playerPosition->y + playerHeight >= tile.y && playerPosition->y <= tile.y + tile.height)
    //     {
    //         SDL_Log("Collision detected");
    //         player->getTransform()->resetLastMoveY();
    //     }
         
    // }
    
    game_engine::Camera::getInstance()->update(dt);
}

void Engine::render() {
    SDL_RenderClear(m_renderer);

    graphics::TextureManager::getInstance()->renderBackground("bg1", 0, 0, 7746, 2324, 0, 0);
    m_levelMap->render();
    player->render();

    SDL_RenderPresent(m_renderer);
}

void Engine::events() {
    Input::getInstance()->listen();
}

} // namespace core