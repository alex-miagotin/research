#include "tile_layer.hpp"

#include <SDL2/SDL.h>

#include "../graphics/texture_manager.hpp"
#include  "../core/engine.hpp"

namespace map
{

TileLayer::TileLayer(int rowsCount, int columnsCount, TileMapLayer tileMapLayer, TilesetList tilesets)
    : m_rowsCount(rowsCount), m_columnsCount(columnsCount), m_tileMapLayer(tileMapLayer), m_tilesets(tilesets)
{
    for (auto& tileset : m_tilesets) {
        graphics::TextureManager::getInstance()->load(tileset.name, tileset.source);
    }

    int index = 0;
    for(auto tile: m_tileMapLayer) {
        if (tile > 0) {
            for (auto tileset : m_tilesets) {
                if (tile >= tileset.firstID && tile <= tileset.lastID) {
                    int tileID = tile - tileset.firstID;
                    int tileRow = tileID / tileset.columnsCount;
                    int tileCol = tileID % tileset.columnsCount;

                    int x = index % m_columnsCount;
                    int y = index / m_columnsCount;

                    m_tiles.push_back(
                        {
                            .textureID = tileset.name,
                            .tileRow = tileRow,
                            .tileCol = tileCol,
                            .width = tileset.tileWidth,
                            .height = tileset.tileHeight,
                            .x = x * tileset.tileWidth,
                            .y = y * tileset.tileHeight
                        }
                    );
                }
            }
        }

        index++;
    }
}

void TileLayer::render()
{
    for (auto& tile : m_tiles) {
        graphics::TextureManager::getInstance()->render(tile.textureID, tile.x, tile.y, tile.width, tile.height, tile.tileRow, tile.tileCol);
    }
}

void TileLayer::update()
{

}

} // namespace map