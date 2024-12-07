#include <SDL2/SDL.h>

#include "../game.hpp"

#include "keyboard_controller.hpp"
#include "transform_component.hpp"

void KeyboardController::init()
{

    // if (!entity->hasComponent<TransformComponent>())
    // {
    //     entity->addComponent<TransformComponent>();
    // }

    transform = &entity->getComponent<TransformComponent>();
}

void KeyboardController::update()
{
    if (Game::event.type == SDL_KEYDOWN)
    {
        if (Game::event.key.keysym.sym == SDLK_w) {
            transform->velocity.y = -1;
        }

        if (Game::event.key.keysym.sym == SDLK_a) {
            transform->velocity.x = -1;
        }

        if (Game::event.key.keysym.sym == SDLK_s) {
            transform->velocity.y = 1;
        }

        if (Game::event.key.keysym.sym == SDLK_d) {
            transform->velocity.x = 1;
        }
    }

    if (Game::event.type == SDL_KEYUP)
    {
        if (Game::event.key.keysym.sym == SDLK_w) {
            transform->velocity.y = 0;
        }

        if (Game::event.key.keysym.sym == SDLK_a) {
            transform->velocity.x = 0;
        }

        if (Game::event.key.keysym.sym == SDLK_s) {
            transform->velocity.y = 0;
        }

        if (Game::event.key.keysym.sym == SDLK_d) {
            transform->velocity.x = 0;
        }
    }
}