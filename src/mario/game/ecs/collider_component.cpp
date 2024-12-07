#include <SDL2/SDL.h>

#include "../game.hpp" // TODO: shoud not include game.hpp. Better to pass the reference to colliders vector as a parameter to the constructor

#include "ecs.hpp"
#include "collider_component.hpp"
#include "transform_component.hpp"

ColliderComponent::ColliderComponent(std::string t)
    : tag(t)
{}

void ColliderComponent::init()
{
    if (!entity->hasComponent<TransformComponent>())
    {
        entity->addComponent<TransformComponent>();
    }

    transform = &entity->getComponent<TransformComponent>();

    Game::colliders.push_back(this);
}

void ColliderComponent::update()
{
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
}