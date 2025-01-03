#include "collision.hpp"

namespace core::physics
{

bool Collision::AABB(const Rect& recA, const Rect& recB)
{
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
    )
    {
        return true;
    }
    return false;
}

bool Collision::CircleCircle(const Circle& cirA, const Circle& cirB)
{
    int x1 = cirA.x;
    int y1 = cirA.y;
    int r1 = cirA.r;

    int x2 = cirB.x;
    int y2 = cirB.y;
    int r2 = cirB.r;

    int dx = x2 - x1;
    int dy = y2 - y1;
    int radii = r1 + r2;

    if ((dx * dx) + (dy * dy) < radii * radii)
    {
        return true;
    }
    return false;
}

} // namespace core::physics