#include <string>
#include <iostream>

#include "SDL_image.h"
#include "SDL2/SDL.h"

#include "map.hpp"
#include "game.hpp"

#include "common/collision.hpp"
#include "ecs/components.hpp"

Map *map;

Manager manager;
auto& newPlayer(manager.addEntity());

SDL_Event Game::event;
SDL_Renderer *Game::renderer = nullptr;
bool Game::isRunning = false;
Rect Game::camera = {0, 0, 800, 640};

AssetManager *Game::assets = new AssetManager(&manager);

auto& tiles(manager.getGroup(Game::groupLabels::groupMap));
auto& players(manager.getGroup(Game::groupLabels::groupPlayers));
auto& colliders(manager.getGroup(Game::groupLabels::groupColliders));
auto& projectiles(manager.getGroup(Game::groupLabels::groupProjectiles));

SDL_Rect rectToSDLRect(const Rect& rect, const Rect& camera = {0, 0, 0, 0})
{
    return { .x = rect.x - camera.x, .y = rect.y - camera.y, .w = rect.w, .h = rect.h };
}

Game::Game()
{
}

Game::~Game()
{
    printf("Game destroyed\n");
}

void Game::init(const Configuration &config)
{
    this->config = config;
    int flags = 0;
    if (config.fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised!..." << std::endl;

        window = SDL_CreateWindow(config.title, config.xpos, config.ypos, config.width, config.height, flags);
        if (window)
        {
            printf("Window created!\n");
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
            std::cout << "Renderer created!..." << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    assets->addTexture("collider", "/images/col_tex.png");
    assets->addTexture("terrain", "/sprites/terrain_ss.png");
    assets->addTexture("player", "/sprites/player/player_anims.png");
    assets->addTexture("projectile", "/images/proj.png");

    map = new Map(manager, 25, 20, config.tileSize, config.scale);
    map->loadMap("/maps/map.map");

    std::map<const char*, Animation> playerAnims = {
        {"idle", Animation(0, 3, 100)},
        {"walk", Animation(1, 8, 100)}
    };
    newPlayer.addComponent<TransformComponent>(Vector2D(config.width / 2, config.height / 2), 32, 32, config.scale);
    newPlayer.addComponent<SpriteComponent>("player", playerAnims, "idle");
    newPlayer.addComponent<ColliderComponent>("player");
    newPlayer.addGroup(groupLabels::groupPlayers);
    newPlayer.addComponent<KeyboardController>();

    assets->createProjectile(Vector2D(400, 600), Vector2D(1, 0), 200, 0, "projectile");

    std::cout << "Game Initialised" << std::endl;
}

void Game::handleEvents()
{
    SDL_PollEvent(&Game::event);
    switch (Game::event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

void Game::update()
{
    Vector2D playerPos = newPlayer.getComponent<TransformComponent>().position;

    manager.refresh();
    manager.update();

    for(auto& c : colliders)
    {
        if(Collision::AABB(newPlayer.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>())) {
            newPlayer.getComponent<TransformComponent>().position = playerPos;
        }
    }

    for(auto& p : projectiles)
    {
        if (Collision::AABB(newPlayer.getComponent<ColliderComponent>(), p->getComponent<ColliderComponent>()))
        {
            std::cout << "Player hit by projectile" << std::endl;
            p->destroy();
        }
    }

    auto playerTransform = newPlayer.getComponent<TransformComponent>();
    camera.x = playerTransform.position.x - config.width / 2;
    camera.y = playerTransform.position.y - config.height / 2;

    if (camera.x < 0)
    {
        camera.x = 0;
    }

    if (camera.y < 0)
    {
        camera.y = 0;
    }

    if (camera.x > camera.w)
    {
        camera.x = camera.w;
    }

    if (camera.y > camera.h)
    {
        camera.y = camera.h;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    
    auto tileTexture = assets->getTexture("terrain");
    for(auto& t : tiles)
    {
        auto tileCompoennt = t->getComponent<TileComponent>();
        auto srcRect = tileCompoennt.getSrcRect();
        auto destRect = tileCompoennt.getDestRect();
        TextureManager::Render(tileTexture, rectToSDLRect(srcRect), rectToSDLRect(destRect, Game::camera), SDL_FLIP_NONE);
    }

    auto colliderTexture = assets->getTexture("collider");
    for(auto& c : colliders)
    {
        auto& collider = c->getComponent<ColliderComponent>().collider;
        TextureManager::Render(colliderTexture, { 0,0,32,32 }, rectToSDLRect(collider, Game::camera), SDL_FLIP_NONE);
    }

    for(auto& p : players)
    {
        p->render();
    }

    for(auto& p : projectiles)
    {
        p->render();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}