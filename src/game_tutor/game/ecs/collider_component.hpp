#pragma once

#include <string>

#include "ecs.hpp"

class TransformComponent;
struct SDL_Rect;

class ColliderComponent : public Component
{
public:
    TransformComponent* transform;
    SDL_Rect collider;
    std::string tag;

    ColliderComponent(std::string);
    ~ColliderComponent() {}

    void init() override;
    void update() override;
};