//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <TileType.h>
#include <Tile.h>
#include <vector>

#define MAP_SIZE 12

using namespace std;

class Map
{
private:
	vector<vector<TileNames>> contentBase = { //Should be generated or loaded from file
		{ GREEN,   GREEN, GREEN,   GREEN,   DEFAULT, DEFAULT },
		{ GREEN,   GREEN, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
		{ GREEN,   GREEN, DEFAULT, GREEN,   DEFAULT, DEFAULT },
		{ GREEN,   GREEN, DEFAULT, DEFAULT, DEFAULT, DEFAULT },
		{ DEFAULT, GREEN, DEFAULT, GREEN,   DEFAULT, DEFAULT },
		{ DEFAULT, GREEN, GREEN,   DEFAULT, DEFAULT, DEFAULT }};
	vector<vector<Tile*>> content;
	vector<TileType*> tile_types;
public:
	Map();
	void fillMap(vector<vector<TileNames>>& map){
		map.resize(MAP_SIZE);
		for(int w=0;w<MAP_SIZE;w++){
			map[w].resize(MAP_SIZE);
			for(int h=0;h<MAP_SIZE;h++){
				map[w][h] = TileNames::DEFAULT;
			}
		}
	}
	vector<vector<Tile*>> &getContent() { return content; }
};


//GBTTD_MAP_H
