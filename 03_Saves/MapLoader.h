//
// Created by fusto on 08.05.22.
//

#pragma once

#include <gbttd.h>

class MapLoader {
private:

	static MapLoader* singleton_;
	MapLoader();
public:
	MapLoader(MapLoader &other) = delete;
	static MapLoader *getInstance();
};


//GBTTD_MAPLOADER_H
