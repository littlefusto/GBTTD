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
	for (int i = 0; i < getSize().x; i++)
	{
		content[i].resize(tileTypes.size());
		for (int j = 0; j < getSize().y; j++)
		{
			content[i][j] = new Tile(1, tileTypes[i][j], FLAT);
		}
	}
}

void Map::fillMap(vector<vector<TileType>> &map) {
	map.resize(getSize().x);
	for (int w = 0; w < getSize().x; w++)
	{
		map[w].resize(getSize().y);
		for (int h = 0; h < getSize().y; h++)
		{
			map[w][h] = TileType::GRASS;
		}
	}
}

Vector2<int> Map::getSize() {
	Vector2<int> vector;
	vector.x = this->x;
	vector.y = this->y;
	return vector;
}