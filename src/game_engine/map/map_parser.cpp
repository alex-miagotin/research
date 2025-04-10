#include <string>
#include <sstream>

#include "map_parser.hpp"

#ifndef ASSETS_PATH
    #define ASSETS_PATH ""
#endif

namespace map
{

MapParser* MapParser::m_instance = nullptr;

void MapParser::clean()
{
    m_maps.clear();
}

bool MapParser::load(const std::string& mapId, const std::string& mapFile)
{
    return parse(mapId, (std::string(ASSETS_PATH) + mapFile));
}

bool MapParser::parse(const std::string &mapId, const std::string &mapFile)
{
    TiXmlDocument doc;
    if (!doc.LoadFile(mapFile.c_str())) {
        std::cerr << "Failed to load map file: " << mapFile << std::endl;
        return false;
    }


    TiXmlElement* root = doc.RootElement();

    int tileWidth, tileHeight;
    int rowsCount, columnsCount;
    root->Attribute("tilewidth", &tileWidth);
    root->Attribute("tileheight", &tileHeight);
    root->Attribute("width", &columnsCount);
    root->Attribute("height", &rowsCount);

    // Parse tilesets
    TilesetList tilesets;
    for (TiXmlElement* xmlTileset = root->FirstChildElement("tileset"); xmlTileset != nullptr; xmlTileset = xmlTileset->NextSiblingElement("tileset")) {
        tilesets.push_back(parseTileSet(xmlTileset));
    }

    // Parse layers
    GameMap* gameMap = new GameMap();
    for (TiXmlElement* xmlLayer = root->FirstChildElement("layer"); xmlLayer != nullptr; xmlLayer = xmlLayer->NextSiblingElement("layer")) {
        gameMap->addLayer(new TileLayer(rowsCount, columnsCount, parseTileLayer(xmlLayer), tilesets));
    }

    m_maps[mapId] = gameMap;
    
    return true;
}

Tileset MapParser::parseTileSet(TiXmlElement* xmlTileset)
{
    Tileset tileset;
    tileset.name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("tilecount", &tileset.tilesCount);

    xmlTileset->Attribute("firstgid", &tileset.firstID);
    tileset.lastID = tileset.firstID + tileset.tilesCount - 1;

    xmlTileset->Attribute("tilewidth", &tileset.tileWidth);
    xmlTileset->Attribute("tileheight", &tileset.tileHeight);
    xmlTileset->Attribute("columns", &tileset.columnsCount);
    tileset.rowsCount = tileset.tilesCount / tileset.columnsCount;

    tileset.source = xmlTileset->FirstChildElement()->Attribute("source");

    return tileset;
}

TileMapLayer MapParser::parseTileLayer(TiXmlElement* xmlLayer)
{
    int rowsCount, columnsCount;
    xmlLayer->Attribute("width" , &columnsCount);
    xmlLayer->Attribute("height", &rowsCount);

    TiXmlElement* data = xmlLayer->FirstChildElement();

    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;
    
    TileMapLayer tileMapLayer{};
    for(int row = 0; row < rowsCount; row++) {
        for(int col = 0; col < columnsCount; col++) {
            getline(iss, id, ',');
            tileMapLayer.push_back(atoi(id.c_str()));

            if (!iss.good()) {
                break;
            }
        }
    }

    return tileMapLayer;
}

} // namespace map