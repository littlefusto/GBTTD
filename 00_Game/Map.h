//
// Created by cpukiller on 06.05.22.
//

#ifndef GBTTD_MAP_H
#define GBTTD_MAP_H

#include <Tile.h>

#define MAP_SIZE 4

class Map {
private:
    TileNames content[MAP_SIZE][MAP_SIZE]= {{RED,RED,RED,RED},
                                           {RED,RED,DEFAULT,DEFAULT},
                                           {DEFAULT,RED,DEFAULT,RED},
                                           {DEFAULT,RED,RED,DEFAULT}};
public:
    Map();
    void getContent(TileNames map_content[MAP_SIZE][MAP_SIZE]) {map_content=content;}
};


#endif //GBTTD_MAP_H
