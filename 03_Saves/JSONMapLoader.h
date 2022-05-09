//
// Created by cpukiller on 09.05.22.
//

#pragma once

#include <gbttd.h>
#include <jsoncpp/json/json.h>

namespace JSONMapLoader {
	void saveMap(Map &map, std::string& path);
	Map* loadMap(std::string& path);
}