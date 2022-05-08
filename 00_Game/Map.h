//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <gbttd.h>

#define MAP_SIZE 6
#define MAX_MAP_HEIGHT 2

using namespace std;

class Map
{
private:
	MapLoader* mapLoader;
	vector<vector<TileType>> tileTypes = { //Should be generated or loaded from file
		{ GRASS,   GRASS, GRASS,   GRASS,   DEFAULT, DEFAULT },
		{ GRASS,   GRASS, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
		{ GRASS,   GRASS, DEFAULT, GRASS,   DEFAULT, DEFAULT },
		{ GRASS,   GRASS, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
		{ DEFAULT, GRASS, DEFAULT, GRASS,   DEFAULT, DEFAULT },
		{ DEFAULT, GRASS, GRASS,   DEFAULT, DEFAULT, DEFAULT }};
	vector<vector<Tile*>> content;
	//vector<vector<sf::Image*>> textures;
public:

	Map();

	void fillMap(vector<vector<TileType>> &map);

	vector<vector<Tile*>> &getContent() { return content; }
};


//GBTTD_MAP_H
