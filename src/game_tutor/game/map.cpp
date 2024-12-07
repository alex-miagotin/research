#include <string>
#include <fstream>

#include "game.hpp"
#include "map.hpp"

#ifndef RESOURCE_PATH
    #define RESOURCE_PATH ""
#endif

Map::Map()
{
    
}

Map::~Map()
{
    
}

void Map::loadMap(std::string path, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(RESOURCE_PATH + path);

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            Game::addTile(atoi(&tile), x * 32, y * 32);
            mapFile.ignore();
        }
    }
    // Game::addTile(*Game::renderer, 0, 0, 0);


    mapFile.close();
}
