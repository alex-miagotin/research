#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "ecs.hpp"
#include "animation.hpp"
#include "transform_component.hpp"

class SpriteComponent : public Component
{
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    bool animated = false;
    int frames = 0;
    int speed = 100;
    int animIndex = 0;
    std::map<const char*, Animation> animations;

public:
    SpriteComponent(const char* textureId);
    SpriteComponent(const char* textureId, const std::map<const char*, Animation>& animations, const char* animName);

    ~SpriteComponent();

    void init() override;
    void update() override;
    void render() override;

    void setTexture(const char* textureId);
    void setFlip(SDL_RendererFlip flip);

    void play(const char* animName);
};