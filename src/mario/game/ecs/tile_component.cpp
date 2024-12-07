#include "SDL2/SDL.h"

#include "transform_component.hpp"
#include "sprite_component.hpp"
#include "tile_component.hpp"


TileComponent::TileComponent(SDL_Renderer* ren, int x, int y, int w, int h, int id)
{
    renderer = ren;
    tileRect.x = x;
    tileRect.y = y;
    tileRect.w = w;
    tileRect.h = h;
    tileID = id;

    switch (tileID)
    {
    case 0:
        path = "/images/water.png";
        break;
    case 1:
        path = "/images/dirt.png";
        break;
    case 2:
        path = "/images/grass.png";
        break;
    default:
        break;
    }
}

void TileComponent::init()
{
    entity->addComponent<TransformComponent>(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), tileRect.w, tileRect.h, 1);
    transform = &entity->getComponent<TransformComponent>();

    entity->addComponent<SpriteComponent>(path, renderer);
    sprite = &entity->getComponent<SpriteComponent>();
}