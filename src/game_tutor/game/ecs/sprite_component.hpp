#pragma once

#include "ecs.hpp"

class TransformComponent;
class SDL_Texture;
class SDL_Renderer;
struct SDL_Rect;

class SpriteComponent : public Component
{
private:
    TransformComponent* transform;    
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent(const char* path, SDL_Renderer* ren);

    ~SpriteComponent();

    void init() override;
    void update() override;
    void render() override;

    void setTexture(const char* path);
};