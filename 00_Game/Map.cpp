//
// Created by cpukiller on 06.05.22.
//

#include <gbttd.h>

Map::Map()
{
	tileTypes.resize(10);
	//fillMap(contentBase);
	content.resize(tileTypes.size());
//	tile_infos[DEFAULT] = new Tile(DEFAULT, FLAT);
//	tile_infos[GRASS] = new Tile(GRASS, FLAT);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		content[i].resize(tileTypes.size());
		for (int j = 0; j < MAP_SIZE; j++)
		{
			content[i][j] = new Tile(tileTypes[i][j], FLAT);
		}
	}
}

void Map::fillMap(vector<vector<TileType>> &map) {
	map.resize(MAP_SIZE);
	for (int w = 0; w < MAP_SIZE; w++)
	{
		map[w].resize(MAP_SIZE);
		for (int h = 0; h < MAP_SIZE; h++)
		{
			map[w][h] = TileType::GRASS;
		}
	}
}