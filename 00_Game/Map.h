//
// Created by cpukiller on 06.05.22.
//

#ifndef GBTTD_MAP_H
#define GBTTD_MAP_H

#include <Tile.h>
#include <vector>

#define MAP_SIZE 6

using namespace std;

class Map {
private:
    vector<vector<TileNames>> content= {{RED,RED,RED,RED,DEFAULT,DEFAULT},
                                       {RED,RED,DEFAULT,DEFAULT,DEFAULT,DEFAULT},
                                       {RED,RED,DEFAULT,RED,DEFAULT,DEFAULT},
                                       {RED,RED,DEFAULT,DEFAULT,DEFAULT,DEFAULT},
                                       {DEFAULT,RED,DEFAULT,RED,DEFAULT,DEFAULT},
                                       {DEFAULT,RED,RED,DEFAULT,DEFAULT,DEFAULT}};
public:
    Map();
    vector<vector<TileNames>>& getContent() {return content;}
};


#endif //GBTTD_MAP_H
