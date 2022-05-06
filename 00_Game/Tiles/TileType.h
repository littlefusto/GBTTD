//
// Created by cpukiller on 06.05.22.
//

#ifndef GBTTD_TILETYPE_H
#define GBTTD_TILETYPE_H

#include <SFML/Graphics.hpp>

enum TileNames {
    DEFAULT=0,
    GREEN=1
};

class TileType {
private:
    TileNames tile_name;
public:
    TileType(TileNames tile_name);
    TileNames getTileTypeId(){return tile_name;}
};


#endif //GBTTD_TILETYPE_H
