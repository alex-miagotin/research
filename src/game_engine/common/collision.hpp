#pragma once

#include "common.hpp"

class Collision
{
public:
    static bool AABB(const Rect& recA, const Rect& recB);
    static bool CircleCircle(const Circle& cirA, const Circle& cirB);
};