#include "tile_component.hpp"

TileComponent::TileComponent(int srcX, int srcY, int xPos, int yPos, int tileSize, int scale)
{
    position.x = xPos;
    position.y = yPos;

    srcRect.x = srcX;
    srcRect.y = srcY;
    srcRect.w = srcRect.h = tileSize;

    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = destRect.h = tileSize * scale;
}

Rect &TileComponent::getDestRect()
{
    return destRect;
}

Rect &TileComponent::getSrcRect()
{
    return srcRect;
}

