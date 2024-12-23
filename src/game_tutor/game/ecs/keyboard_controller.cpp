#include <SDL2/SDL.h>

#include "../game.hpp"

#include "keyboard_controller.hpp"
#include "transform_component.hpp"
#include "sprite_component.hpp"

void KeyboardController::init()
{
    // if (!entity->hasComponent<TransformComponent>())
    // {
    //     entity->addComponent<TransformComponent>();
    // }

    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
}

void KeyboardController::update()
{
    auto transform = &entity->getComponent<TransformComponent>();
    auto sprite = &entity->getComponent<SpriteComponent>();

    if (Game::event.type == SDL_KEYDOWN)
    {
        if (Game::event.key.keysym.sym == SDLK_w) {
            transform->velocity.y = -1;
            sprite->play("walk");
        }

        if (Game::event.key.keysym.sym == SDLK_a) {
            transform->velocity.x = -1;
            sprite->setFlip(SDL_FLIP_HORIZONTAL);
            sprite->play("walk");
        }

        if (Game::event.key.keysym.sym == SDLK_s) {
            transform->velocity.y = 1;
            sprite->play("walk");
        }

        if (Game::event.key.keysym.sym == SDLK_d) {
            transform->velocity.x = 1;
            sprite->setFlip(SDL_FLIP_NONE);
            sprite->play("walk");
        }
    }

    if (Game::event.type == SDL_KEYUP)
    {
        if (Game::event.key.keysym.sym == SDLK_w) {
            transform->velocity.y = 0;
            sprite->play("idle");
        }

        if (Game::event.key.keysym.sym == SDLK_a) {
            transform->velocity.x = 0;
            sprite->play("idle");
        }

        if (Game::event.key.keysym.sym == SDLK_s) {
            transform->velocity.y = 0;
            sprite->play("idle");
        }

        if (Game::event.key.keysym.sym == SDLK_d) {
            transform->velocity.x = 0;
            sprite->play("idle");
        }

        if (Game::event.key.keysym.sym == SDLK_ESCAPE) {
            Game::isRunning = false;
        }
    }
}