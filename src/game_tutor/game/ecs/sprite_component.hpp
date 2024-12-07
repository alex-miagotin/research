#pragma once

#include "ecs.hpp"

class TransformComponent;
class SDL_Texture;
struct SDL_Rect;

class SpriteComponent : public Component
{
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent(const char* path);

    ~SpriteComponent();

    void init() override;
    void update() override;
    void render() override;

    void setTexture(const char* path);
};