//
// Created by fusto on 06.05.22.
//

#include <gbttd.h>
#include "Tile.h"


Tile::Tile( int heightTemp, TileType tile_typeTemp, Slope slopeTemp ){
	if(heightTemp<=MAX_MAP_HEIGHT && heightTemp>= 0 && tile_typeTemp>=DEFAULT && tile_typeTemp<= GRASS && slopeTemp>=FLAT && slopeTemp<= STEEP_N) {
		height = heightTemp;
		tile_type = tile_typeTemp;
		slope = slopeTemp;
	} else {
		throw std::invalid_argument("Tile arguments incorrect");
	}
}

Tile::Tile()
= default;
