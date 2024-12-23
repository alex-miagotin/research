#include <SDL2/SDL.h>

#include "../game.hpp"
#include "sprite_component.hpp"
#include "../texture_manager.hpp"
#include "animation.hpp"

SpriteComponent::SpriteComponent(const char* textureId)
{
    setTexture(textureId);
}

SpriteComponent::SpriteComponent(const char* textureId, const std::map<const char*, Animation>& _animations, const char* animName): animations(_animations)
{
    // Animation idle = Animation(0, 3, 150);
    // Animation walk = Animation(1, 8, 150);

    // animations.emplace("idle", idle);
    // animations.emplace("walk", walk);

    play(animName);

    setTexture(textureId);
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::setTexture(const char* textureId)
{
    // if (!entity->hasComponent<TransformComponent>())
    // {
    //     entity->addComponent<TransformComponent>();
    // }

    texture = Game::assets->getTexture(textureId);
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
    if (animations.size() > 0)
    {
        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks64() / speed) % frames);
    }

    srcRect.y = animIndex * transform->height;

    destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
    destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
}

void SpriteComponent::render()
{
    TextureManager::Render(texture, srcRect, destRect, spriteFlip);
}

void SpriteComponent::setFlip(SDL_RendererFlip flip)
{
    spriteFlip = flip;
}

void SpriteComponent::play(const char* animName)
{
    frames = animations[animName].frames;
    speed = animations[animName].speed;
    animIndex = animations[animName].index;
}
