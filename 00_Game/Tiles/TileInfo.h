//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <gbttd.h>

enum Slope : unsigned char//bitflag N E S W dictates high corners
{
	FLAT = 0, N = 0b1000, E = 0b0100, S = 0b0010, W = 0b0001,
	NE = (N | E), NES = (N | E | S), NEW = (N | E | W), NS = (N | S), NSW = (N | S | W), NW = (N | W),
	ES = (E | S), ESW = (E | S | W), SW = (S | W),
	NESW = (N | E | S | W),
	STEEP = 0b10000, STEEP_N = (STEEP | N), STEEP_E = (STEEP | E), STEEP_S = (STEEP | S), STEEP_W = (STEEP | W)
};

enum TileType : unsigned char
{
	DEFAULT = 0,
	GRASS = 1
};

class TileInfo
{
private:
	sf::Image tile_image;
	TileType tile_type;
	Slope slope = FLAT;
public:
	TileInfo(sf::Image* tile_image, TileType tile_type);

	Slope getTileSlope() const { return slope; }

	TileType getTileType() const { return tile_type; }

	sf::Image &getTileImage() { return tile_image; }
};


//GBTTD_TILETYPE_H
