//
// Created by cpukiller on 06.05.22.
//

#ifndef GBTTD_MAP_H
#define GBTTD_MAP_H

#include <TileType.h>
#include <Tile.h>
#include <vector>

#define MAP_SIZE 6

using namespace std;

class Map
{
private:
	vector<vector<TileNames>> contentBase = { //Should be generated or loaded from file
            { GREEN,    GREEN,      GREEN,      GREEN,      DEFAULT,    DEFAULT },
            { GREEN,    GREEN,      DEFAULT,    DEFAULT,    DEFAULT,    DEFAULT },
            { GREEN,    GREEN,      DEFAULT,    GREEN,      DEFAULT,    DEFAULT },
            { GREEN,    GREEN,      DEFAULT,    DEFAULT,    DEFAULT,    DEFAULT },
            { DEFAULT,  GREEN,      DEFAULT,    GREEN,      DEFAULT,    DEFAULT },
            { DEFAULT,  GREEN,      GREEN,      DEFAULT,    DEFAULT,    DEFAULT }};
    vector<vector<Tile*>> content;
    vector<TileType*> tile_types;
public:
	Map();

	vector<vector<Tile*>> &getContent() { return content; }
};


#endif //GBTTD_MAP_H
