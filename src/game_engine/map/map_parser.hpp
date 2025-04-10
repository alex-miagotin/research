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

    bool load(const std::string &mapId, const std::string &mapFile);
    void clean();

    inline GameMap* getMap(const std::string &id) { return m_maps[id]; }

private:
    bool parse(const std::string &mapId, const std::string& mapFile);
    Tileset parseTileSet(TiXmlElement* xmlTileset);
    TileMapLayer parseTileLayer(TiXmlElement* xmlLayer);

private:
    MapParser() = default;
    static MapParser* m_instance;

    std::map<const std::string, GameMap*> m_maps;
};

} // namespace map