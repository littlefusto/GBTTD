//
// Created by cpukiller on 06.05.22.
//

#include <gbttd.h>


Map::Map()
{
	tile_infos.resize(10);
	//fillMap(contentBase);
	content.resize(contentBase.size());
	textures textures{};
	tile_infos[DEFAULT] = new TileInfo(textures.tiles + "tile.png", DEFAULT);
	tile_infos[GRASS] = new TileInfo(textures.tiles + "grass_flat.png", GRASS);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		content[i].resize(contentBase.size());
		for (int j = 0; j < MAP_SIZE; j++)
		{
			content[i][j] = new Tile(tile_infos[contentBase[i][j]]);
		}
	}
}

std::string Map::TileSlopePath(Slope slope)
{
	std::string path;
	if (!slope)return "flat";
	if (slope & STEEP)
	{
		path += "steep_";
		switch (slope & NESW)
		{
		case N:
			return path += "N";
		case E:
			return path += "E";
		case S:
			return path += "S";
		case W:
			return path += "W";
		default:
			throw std::invalid_argument("invalid arguments: tile is improperly constructed");
		}
	} else
	{
		path += "sloped_";
		if (slope & N)path += "N";
		if (slope & E)path += "E";
		if (slope & S)path += "S";
		if (slope & W)
		{
			if ((slope & NES) == NES)//if sloped in all directions tile is invalid
			{
				throw std::invalid_argument(
					"improperly constructed tile: cannot have a tile with NESW flags set");
			} else { path += "W"; }
		}
	}

	return path;
}
