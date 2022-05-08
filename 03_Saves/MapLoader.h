//
// Created by fusto on 08.05.22.
//

#pragma once

#include <gbttd.h>

class MapLoader {
private:
	int mapXsize;
	int mapYsize;
	static MapLoader* singleton_;
	static std::string saveTile(Tile* tile);
	static std::string getAttribute(std::string tileString, std::string attribute);
	static Tile* loadTile(std::string tileString);

public:
	MapLoader();

	void saveMap(Map& map, std::string name);
	void loadMap(Map& map, std::string name);
	static MapLoader *getInstance();

};


//GBTTD_MAPLOADER_H
