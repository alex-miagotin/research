#include <SDL2/SDL.h>

#include "sprite_component.hpp"
#include "transform_component.hpp"
#include "../texture_manager.hpp"
#include "ecs.hpp"

SpriteComponent::SpriteComponent(const char* path, SDL_Renderer* ren) : renderer(ren)
{
    setTexture(path);
}

SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(texture);
}

void SpriteComponent::setTexture(const char* path)
{
    // if (!entity->hasComponent<TransformComponent>())
    // {
    //     entity->addComponent<TransformComponent>();
    // }

    texture = TextureManager::LoadTexture(path, renderer);
}

void SpriteComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = transform->width;
    srcRect.h = transform->height;

    short scale = transform->scale;
    destRect.w = transform->width * scale;
    destRect.h = transform->height * scale;
}

void SpriteComponent::update()
{
    destRect.x = static_cast<int>(transform->position.x);
    destRect.y = static_cast<int>(transform->position.y);
}

void SpriteComponent::render()
{
    TextureManager::Render(renderer, texture, srcRect, destRect);
}

