#pragma once

#include <map>

#include "tinyxml.h"

#include "game_map.hpp"
#include "tile_layer.hpp"

namespace map
{

class MapParser
{
public:
    static MapParser* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new MapParser();
        }
        return m_instance;
    }

    bool load();
    void clean();

    inline GameMap* getMap(const char* id) { return m_maps[id]; }

private:
    bool parse(const char* mapId, const char* mapFile);
    Tileset parseTileSet(TiXmlElement* xmlTileset);
    TileMapLayer parseTileLayer(TiXmlElement* xmlLayer);

private:
    MapParser() = default;
    static MapParser* m_instance;

    std::map<const char*, GameMap*> m_maps;
};

} // namespace map