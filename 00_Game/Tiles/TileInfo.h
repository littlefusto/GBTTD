//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <SFML/Graphics.hpp>

enum Slope //bitflag N E S W dictates high corners
{
	FLAT = 0,
	W = 0b0001,
	S = 0b0010,
	E = 0b0100,
	N = 0b1000,
	NES = 0b1110,
	NESW = 0b1111,
	STEEP = 0b10000,
	STEEP_N = 0b11000,
	STEEP_E = 0b10100,
	STEEP_S = 0b10010,
	STEEP_W = 0b10001,
	STEEP_NES = 0b11110,
	STEEP_NSW = 0b11011,
	STEEP_ESW = 0b10111,
	STEEP_NEW = 0b11101
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
	TileInfo(std::string image_path, TileType tile_type);

	sf::Image &getTileImage() { return tile_image; }
};


//GBTTD_TILETYPE_H
