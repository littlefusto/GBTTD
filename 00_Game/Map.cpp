//
// Created by cpukiller on 06.05.22.
//

#include <algorithm>
#include "Map.h"
#include <Textures.h>

std::string Map::TileSlopePath(slope slope)
{
	std::string path;
	if (!slope) { return "flat"; }
	else if (slope & STEEP) { path += "steep_"; } else { path += "sloped_"; }
	if (slope & N)path += "N";
	if (slope & E)path += "E";
	if (slope & S)path += "S";
	if (slope & W)path += "W";
	return path;
}

Map::Map()
{
	tile_types.resize(10);
	//fillMap(contentBase);
	content.resize(contentBase.size());
	textures textures{};
	tile_types[DEFAULT] = new TileType(textures.tiles + "tile.png", DEFAULT);;
	tile_types[GRASS] = new TileType(textures.tiles + "grass_flat.png", GRASS);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		content[i].resize(contentBase.size());
		for (int j = 0; j < MAP_SIZE; j++)
		{
			content[i][j] = new Tile(tile_types[contentBase[i][j]]);
		}
	}
}
