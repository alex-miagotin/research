#pragma once

#include <vector>

#include "layer.hpp"
#include "../core/common.hpp"

namespace map
{

struct Tileset
{
    int firstID;
    int lastID;
    int rowsCount;
    int columnsCount;
    int tileWidth;
    int tileHeight;
    int tilesCount;
    
    const char* name;
    const char* source;
};

using TilesetList = std::vector<Tileset>;
using TileMapLayer = std::vector<int>;
using TileMapLayers = std::vector<TileMapLayer >;

class TileLayer: public Layer
{

public:
    struct Tile
    {
        const char* textureID;
        int tileRow;
        int tileCol;
        int width;
        int height;
        int x;
        int y;
    };

public:
    TileLayer(int rowsCount, int columnsCount, TileMapLayer tileMapLayer, TilesetList tilesets);

    void render() override;
    void update() override;

    inline TileMapLayer& getTileMapLayer() { return m_tileMapLayer; }
    inline TilesetList& getTilesets() { return m_tilesets; }
    inline std::vector<Tile>& getTiles() { return m_tiles; }

private:
    int m_rowsCount;
    int m_columnsCount;

    TileMapLayer m_tileMapLayer;
    TilesetList m_tilesets;
    std::vector<Tile> m_tiles{};
};

} // namespace map