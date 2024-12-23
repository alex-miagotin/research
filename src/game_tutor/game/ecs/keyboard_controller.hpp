#pragma once

#include "ecs.hpp"
#include "transform_component.hpp"
#include "sprite_component.hpp"

class KeyboardController : public Component
{
private:
    TransformComponent* transform;
    SpriteComponent* sprite;

public:
    void init() override;
    void update() override; 
};