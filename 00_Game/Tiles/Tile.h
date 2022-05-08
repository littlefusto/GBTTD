//
// Created by fusto on 06.05.22.
//

#pragma once

#define TILE_WIDTH 64
#define TILE_HEIGTH 32

#include <gbttd.h>

class Tile
{
private:
	TileInfo* tile_info;
	int height = 2;
	Slope slope = FLAT;

public:
	Tile(TileInfo* tile_info);

	int getHeight() const { return height; }

	TileInfo* getTileInfo() const { return tile_info; }
};


//GBTTD_TILE_H
