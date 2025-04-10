#include "transform_component.hpp"

namespace core::components
{

TransformComponent::TransformComponent()
{
    position = Vector2D();
}

TransformComponent::TransformComponent(const float &x, const float &y)
{
    position = Vector2D(x, y);
}

void TransformComponent::translateX(const float &dx)
{
    position.x += dx;
}

void TransformComponent::translateY(const float &dy)
{
    position.y += dy;
}

void TransformComponent::translate(const Vector2D &vec)
{
    position += vec;
}

const TransformComponent::Vector2D *TransformComponent::getPosition()
{
    return &position;
}

void TransformComponent::setPosition(const Vector2D &vec)
{
    position = vec;
}

} // namespace core.components