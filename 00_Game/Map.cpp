//
// Created by cpukiller on 06.05.22.
//

#include <algorithm>
#include "Map.h"
#include <Textures.h>

Map::Map() {
    tile_types.resize(10);
    content.resize(contentBase.size());
    tile_types[DEFAULT] = new TileType(textures::tiles + "tile.png",DEFAULT);;
    tile_types[GREEN] = new TileType(textures::tiles + "tile2.png",GREEN);
    for(int i = 0; i < MAP_SIZE; i++) {
        content[i].resize(contentBase.size());
        for (int j = 0; j < MAP_SIZE; j++) {
            content[i][j] = new Tile(tile_types[contentBase[i][j]]);
        }
    }
}
