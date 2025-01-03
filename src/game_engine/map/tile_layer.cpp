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
}

void TileLayer::render()
{
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

                    SDL_Rect destRect = {x * tileset.tileWidth, y * tileset.tileHeight, tileset.tileWidth, tileset.tileHeight};

                    graphics::TextureManager::getInstance()->render(tileset.name, x * tileset.tileWidth, y * tileset.tileHeight, tileset.tileWidth, tileset.tileHeight, tileRow, tileCol);
                }
            }
        }

        index++;
    }
}

void TileLayer::update()
{

}

} // namespace map