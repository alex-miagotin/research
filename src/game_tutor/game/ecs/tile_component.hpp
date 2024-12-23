#pragma once

#include "../common/common.hpp"
#include "../common/vector2D.hpp"
#include "ecs.hpp"

class TileComponent : public Component
{
public:

    TileComponent() = default;
    TileComponent(int srcX, int srcY, int xPos, int yPos, int tileSize, int scale);

    Rect &getSrcRect();
    Rect &getDestRect();
    

private:
    Rect srcRect, destRect;
    Vector2D position;
};
