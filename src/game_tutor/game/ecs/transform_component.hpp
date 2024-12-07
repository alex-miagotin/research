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

    int speed = 1;

    TransformComponent();
    TransformComponent(float x, float y);
    TransformComponent(float x, float y, int h, int w, int s);

    void init() override;
    void update() override;
};