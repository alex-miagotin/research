#pragma once

#include "common.hpp"

class ColliderComponent;

class Collision
{
public:
    static bool AABB(const Rect& recA, const Rect& recB);
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};