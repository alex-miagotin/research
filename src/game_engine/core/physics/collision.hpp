#pragma once

#include "../common.hpp"

namespace core::physics
{

using namespace core::common;

class Collision
{
public:
    static bool AABB(const Rect& recA, const Rect& recB);
    static bool CircleCircle(const Circle& cirA, const Circle& cirB);
};

} // namespace core::physics