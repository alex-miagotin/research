#pragma once

/**
 * @brief The Map class
 */

class Manager;

class Map {
public:

    Map(Manager& manager, int sizeX, int sizeY, int tileSize, int scale);
    ~Map();

    /**
     * @brief Load a map from a file
     * @param textureId The id of the texture
     * @param sizeX The size of the map in the x direction
     * @param sizeY The size of the map in the y direction
     * @param tileSize The size of the tiles
     * @param scale The scale of the tiles
     */
    void loadMap(const char* path);

private:
    /**
     * @brief Add a tile to the game
     * @param x The x position of the tile
     * @param y The y position of the tile
     * @param xPos The x position of the tile on the screen
     * @param yPos The y position of the tile on the screen
     * @param tileSize The size of the tile
     * @param scale The scale of the tile
     */
    void addTile(int x, int y, int xPos, int yPos, int tileSize, int scale);
    
    int sizeX;
    int sizeY;
    int tileSize;
    int scale;
    Manager& manager;
};