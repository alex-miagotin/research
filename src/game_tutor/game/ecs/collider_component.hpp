#pragma once

#include "../common/common.hpp"

#include "ecs.hpp"

class ColliderComponent : public Component
{
public:
    Rect collider;
    const char* tag;

    ColliderComponent(const char* tag);
    /**
     * @brief Construct a new Collider Component object
     * @param tag The tag of the collider
     * @param xpos The x position of the collider
     * @param ypos The y position of the collider
     * @param size The size of the collider
     */
    ColliderComponent(const char* tag, int xpos, int ypos, int size);
    ~ColliderComponent() {}

    void init() override;
    void update() override;
};