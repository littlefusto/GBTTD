//
// Created by fusto on 06.05.22.
//

#ifndef GBTTD_TILE_H
#define GBTTD_TILE_H

#define TILE_WIDTH 64
#define TILE_HEIGTH 32

#include <TileType.h>

class Tile {
private:
    TileType* tile_type;

public:
    Tile(TileType* tileType);
    TileType* getTileType() {return tile_type;}
};


#endif //GBTTD_TILE_H
