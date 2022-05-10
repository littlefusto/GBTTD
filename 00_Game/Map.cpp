//
// Created by cpukiller on 06.05.22.
//

#include <gbttd.h>

Map::Map(int width, int height){
	x = width;
	y = height;
	content.resize(y);
	for (int i = 0; i < y; i++)
	{
		content[i].resize(x);
		for (int j = 0; j < getSize().x; j++)
		{
			content[i][j] = new Tile(1, GRASS, FLAT);
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

Tile* Map::getTile(int x, int y) {
	if(x<0 || x >= this->x || y < 0 || y >= this->y) return nullptr;
	return content[y][x];
}

Vector2<int> Map::getSize() {
	Vector2<int> vector;
	vector.x = this->x;
	vector.y = this->y;
	return vector;
}