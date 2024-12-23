#pragma once

#include "ecs.hpp"
#include "../common/vector2D.hpp"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 2;

    TransformComponent();
    TransformComponent(Vector2D position);
    TransformComponent(Vector2D position, int h, int w, int scale);

    void init() override;
    void update() override;
};