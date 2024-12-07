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
auto& wall(manager.addEntity());
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Game::Game()
{
}

Game::~Game()
{
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
            // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
            std::cout << "Renderer created!..." << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    map = new Map(renderer);

    tile0.addComponent<TileComponent>(renderer, 200, 200, 32, 32, 0);

    tile1.addComponent<TileComponent>(renderer, 268, 200, 32, 32, 1);
    tile1.addComponent<ColliderComponent>("dirt");

    tile2.addComponent<TileComponent>(renderer, 300, 200, 32, 32, 2);
    tile2.addComponent<ColliderComponent>("grass");

    newPlayer.addComponent<TransformComponent>();
    newPlayer.addComponent<KeyboardController>();
    newPlayer.addComponent<SpriteComponent>("/images/MarioIdle.png", renderer);
    newPlayer.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("/images/wall.png", renderer);
    wall.addComponent<ColliderComponent>("wall");
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
    manager.refresh();
    manager.update();

    for (auto cc : colliders)
    {
        Collision::AABB(newPlayer.getComponent<ColliderComponent>(), *cc);
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    
    // This is where we would add stuff to render
    // map->render();
    manager.render();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
