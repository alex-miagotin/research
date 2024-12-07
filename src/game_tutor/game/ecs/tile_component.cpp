#include "SDL2/SDL.h"

#include "transform_component.hpp"
#include "sprite_component.hpp"
#include "tile_component.hpp"



TileComponent::TileComponent(int x, int y, int w, int h, int id)
{
    tileRect.x = x;
    tileRect.y = y;
    tileRect.w = w;
    tileRect.h = h;
    tileID = id;

    switch (tileID)
    {
    case 0:
        path = "/images/dirt.png";
        break;
    case 1:
        path = "/images/grass.png";
        break;
    case 2:
        path = "/images/water.png";
        break;
    default:
        break;
    }
}

void TileComponent::init()
{
    entity->addComponent<TransformComponent>(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), tileRect.w, tileRect.h, 1);
    transform = &entity->getComponent<TransformComponent>();

    entity->addComponent<SpriteComponent>(path);
    sprite = &entity->getComponent<SpriteComponent>();
}