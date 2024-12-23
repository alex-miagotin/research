#pragma once

#include "ecs.hpp"
#include "transform_component.hpp"

#include "../common/vector2D.hpp"

class ProjectileComponent : public Component
{
public:
    ProjectileComponent(int rng, int sp, Vector2D vel);
    ~ProjectileComponent();

    void init() override;
    void update() override;

private:
    TransformComponent* transform;

    int range = 0;
    int speed = 0;
    int distance = 0;
    Vector2D velocity;
};
