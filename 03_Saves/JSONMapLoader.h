//
// Created by cpukiller on 09.05.22.
//

#pragma once

#include <gbttd.h>

#ifdef _WIN32
#define PATH_DELIMITER "\\"
#else
#define PATH_DELIMITER "/"
#endif

namespace JSONMapLoader {
	void saveMap(Map* map, std::string& path);
	Map* loadMap(std::string& path);
}