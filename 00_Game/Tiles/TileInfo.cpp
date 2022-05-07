//
// Created by cpukiller on 06.05.22.
//

#include "TileInfo.h"

TileInfo::TileInfo(std::string image_path, TileType tile_type) : tile_type(tile_type)
{
	if (!tile_image.loadFromFile(image_path))
	{
		throw std::invalid_argument("Image at" + image_path + " not found");
	}
}
