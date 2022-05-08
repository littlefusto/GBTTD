//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <gbttd.h>

enum Slope //bitflag N E S W dictates high corners
{
	FLAT = 0,
	N = 0b1000,
	E = 0b0100,
	S = 0b0010,
	W = 0b0001,
	NES = 0b1110,
	NESW = 0b1111,
	STEEP = 0b10000,
	STEEP_N = 0b11000,
	STEEP_E = 0b10100,
	STEEP_S = 0b10010,
	STEEP_W = 0b10001
};

enum TileType
{
	DEFAULT = 0,
	GRASS = 1
};

class TileInfo
{
private:
	sf::Image tile_image;
	TileType tile_type;
	Slope slope;
public:
	TileInfo(sf::Image* tile_image, TileType tile_type);

	Slope getTileSlope() {return slope; }
	TileType getTileType() {return tile_type; }
	sf::Image &getTileImage() { return tile_image; }
};


//GBTTD_TILETYPE_H
