#pragma once

#include "ecs.hpp"

class TransformComponent;

class KeyboardController : public Component
{
private:
    TransformComponent* transform;

public:
    void init() override;
    void update() override; 
};