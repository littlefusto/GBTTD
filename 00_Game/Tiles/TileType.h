//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <SFML/Graphics.hpp>

enum slope //bitflag N E S W dictates high corners
{
	FLAT = 0,
	W = 0b0001,
	S = 0b0010,
	E = 0b0100,
	N = 0b1000,
	STEEP = 0b10000,
};

enum TileNames
{
	DEFAULT = 0,
	GRASS = 1
};

class TileType
{
private:
	sf::Image tile_image;
	TileNames tile_name;
	slope slope;
public:
	TileType(std::string image_path, TileNames tile_name);

	sf::Image &getTileImage() { return tile_image; }
};


//GBTTD_TILETYPE_H
