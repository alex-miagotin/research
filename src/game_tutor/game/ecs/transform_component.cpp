#include "transform_component.hpp"

TransformComponent::TransformComponent()
    : position(0, 0) {}

TransformComponent::TransformComponent(Vector2D _position)
    : position(_position) {}

TransformComponent::TransformComponent(Vector2D _position, int h, int w, int scale): position(_position), height(h), width(w), scale(scale) {}

void TransformComponent::init()
{
    velocity.zero();
}
void TransformComponent::update()
{
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
}