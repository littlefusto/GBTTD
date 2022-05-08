//
// Created by fusto on 08.05.22.
//

#pragma once

#include <gbttd.h>


class MapLoader {
private:
	static MapLoader* singleton_;
	std::string saveTile(Tile* tile);

public:
	MapLoader();

	MapLoader(MapLoader &other) = delete;

	void saveMap(std::string name);
	static MapLoader *getInstance();

};


//GBTTD_MAPLOADER_H
