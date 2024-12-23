#include "ecs.hpp"
#include "transform_component.hpp"
#include "../texture_manager.hpp"

#include "collider_component.hpp"

ColliderComponent::ColliderComponent(const char* tag)
    : tag(tag), collider({ 0, 0, 0, 0 })
{}

ColliderComponent::ColliderComponent(const char* tag, int xpos, int ypos, int size)
    : tag(tag), collider({ xpos, ypos, size, size })
{}

void ColliderComponent::init()
{
    if (!entity->hasComponent<TransformComponent>())
    {
        entity->addComponent<TransformComponent>();
    }
}

void ColliderComponent::update()
{
    auto transform = &entity->getComponent<TransformComponent>();
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
}
