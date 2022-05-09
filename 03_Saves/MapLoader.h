//
// Created by fusto on 08.05.22.
//

#pragma once

#include <gbttd.h>

class MapLoader {
private:
	int mapXsize = -1;
	int mapYsize = -1;
	static MapLoader* singleton_;
	static std::string saveTile(Tile* tile);
	static std::string getAttribute(const std::string& tileString, const std::string& attribute);
	static Tile* loadTile(const std::string& tileString);

public:
	MapLoader();

	void saveMap(Map& map, const std::string& name);
	void loadMap(Map& map, const std::string& name);
	static MapLoader *getInstance();

};


//GBTTD_MAPLOADER_H
