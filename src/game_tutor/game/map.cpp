#include <string>
#include <fstream>
#include <iostream>

#include "SDL2/SDL.h"

#include "game.hpp"
#include "map.hpp"
#include "ecs/ecs.hpp"
#include "common/vector2D.hpp"
#include "ecs/tile_component.hpp"
#include "ecs/collider_component.hpp"
#include "ecs/transform_component.hpp"

#ifndef RESOURCE_PATH
    #define RESOURCE_PATH ""
#endif

Map::Map(Manager& _manager, int sizeX, int sizeY, int tileSize, int scale): manager{_manager}, sizeX(sizeX), sizeY(sizeY), tileSize(tileSize), scale(scale)
{
    
}

Map::~Map()
{
    
}

void Map::loadMap(const char* path)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(RESOURCE_PATH + std::string(path));

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile); // read Y
            int srcY = atoi(&tile) * tileSize;

            mapFile.get(tile); // read X
            int srcX = atoi(&tile) * tileSize;

            addTile(srcX, srcY, x * tileSize * scale, y * tileSize * scale, tileSize, scale);
            mapFile.ignore(); // skip next character
        }
    }

    char collider;
    std::fstream collideFile;
    collideFile.open(RESOURCE_PATH + std::string("/maps/colliders.map"));
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            collideFile.get(collider);
            if (collider == '1')
            {
                auto& tcol(manager.addEntity());
                tcol.addComponent<TransformComponent>(Vector2D(x * tileSize * scale, y * tileSize * scale), tileSize, tileSize, scale);
                tcol.addComponent<ColliderComponent>("terrain");
                tcol.addGroup(Game::groupColliders);
            }
            collideFile.ignore();
        }
    }

    collideFile.close();
    mapFile.close();

    std::cout << "Map loaded!" << std::endl;
}

void Map::addTile(int srcX, int srcY, int xPos, int yPos, int tileSize, int scale)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, tileSize, scale);
    tile.addGroup(Game::groupMap);
}
