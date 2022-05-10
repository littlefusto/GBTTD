//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <gbttd.h>

#define MAX_MAP_HEIGHT 16

using namespace std;

class Map
{
private:
	int x = 6;
	int y = 6;
	vector<vector<Tile*>> content;
public:

	Map(int width, int height);
	~Map();

	void fillMap(vector<vector<TileType>> &map);

	Vector2<int> getSize();

	vector<vector<Tile*>> &getContent() { return content; }

	Tile* getTile(int x, int y);
};


//GBTTD_MAP_H
