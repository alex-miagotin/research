#include "transform_component.hpp"
#include "../common/vector2D.hpp"

TransformComponent::TransformComponent()
    : position(0, 0) {}

TransformComponent::TransformComponent(float x, float y)
    : position(x, y) {}

TransformComponent::TransformComponent(float x, float y, int h, int w, int s): position(x, y), height(h), width(w), scale(s) {}

void TransformComponent::init()
{
    velocity.zero();
}
void TransformComponent::update()
{
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
}