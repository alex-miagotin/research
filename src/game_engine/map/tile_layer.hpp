#pragma once

#include <vector>

#include "layer.hpp"

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
    TileLayer(int rowsCount, int columnsCount, TileMapLayer tileMapLayer, TilesetList tilesets);

    void render() override;
    void update() override;

    inline TileMapLayer& getTileMapLayer() { return m_tileMapLayer; }
    inline TilesetList& getTilesets() { return m_tilesets; }

private:
    int m_rowsCount;
    int m_columnsCount;

    TileMapLayer m_tileMapLayer;
    TilesetList m_tilesets;
};

} // namespace map