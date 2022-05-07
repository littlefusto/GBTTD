//
// Created by fusto on 06.05.22.
//

#pragma once

#define TILE_WIDTH 64
#define TILE_HEIGTH 32

#include <TileInfo.h>

class Tile
{
private:
	TileInfo* tile_info;

public:
	Tile(TileInfo* tileInfo);

	TileInfo* getTileInfo() { return tile_info; }
};


//GBTTD_TILE_H
