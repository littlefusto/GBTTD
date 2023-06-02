//
// Created by fusto on 06.05.22.
//

#include <gbttd.h>


Tile::Tile(int heightTemp, TileType tile_typeTemp, Slope slopeTemp)
{
	if (heightTemp <= MAX_MAP_HEIGHT && heightTemp >= 0 && tile_typeTemp >= DEFAULT && tile_typeTemp <= GRASS &&
		slopeTemp >= FLAT && slopeTemp <= STEEP_N)
	{
		height = heightTemp;
		tile_type = tile_typeTemp;
		slope = slopeTemp;
		registered_slope_change = INVALID;
	} else
	{
		throw std::invalid_argument("Tile arguments incorrect");
	}
}

bool Tile::updateSlope(unsigned char* cornerHeights) {
	unsigned char minHeight = min(min(cornerHeights[0], cornerHeights[1]), min(cornerHeights[2], cornerHeights[3]));
	unsigned char maxHeight = max(max(cornerHeights[0], cornerHeights[1]), max(cornerHeights[2], cornerHeights[3]));
	this->slope = FLAT;
	this->height = minHeight;
	// Should not happen. Can be used for debug purposes.
	if (maxHeight - minHeight > 2) {
		return false;
	}
	// steep tile
	if (maxHeight - minHeight == 2) {
		if (cornerHeights[0] == maxHeight && cornerHeights[2] == minHeight) this->slope = STEEP_N;
		else if (cornerHeights[1] == maxHeight && cornerHeights[3] == minHeight) this->slope = STEEP_E;
		else if (cornerHeights[2] == maxHeight && cornerHeights[0] == minHeight) this->slope = STEEP_S;
		else if (cornerHeights[3] == maxHeight && cornerHeights[1] == minHeight) this->slope = STEEP_W;
		else return false; // steep tile but high corner is not opposite to low corner
		return true;
	}
	// mark corners raised if they are heigher than the lowest corner
	for (unsigned char i = 0; i < 4; i++) {
		if (cornerHeights[i] > minHeight) {
			this->slope = (Slope) (this->slope | N >> i);
		}
	}
	return true;
}

Tile::Tile()
= default;