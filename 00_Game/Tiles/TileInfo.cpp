//
// Created by cpukiller on 06.05.22.
//

#include <gbttd.h>

TileInfo::TileInfo(sf::Image* tile_image, TileType tile_type) : tile_type(tile_type)
{
	slope = FLAT;
}
