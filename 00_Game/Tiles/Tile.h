//
// Created by fusto on 06.05.22.
//

#pragma once

#define TILE_WIDTH 64
#define TILE_HEIGHT 32

#include <gbttd.h>

enum Slope : unsigned char {//bitflag N E S W dictates high corners
	FLAT = 0, N = 0b1000, E = 0b0100, S = 0b0010, W = 0b0001,
	NE = (N | E), NES = (N | E | S), NEW = (N | E | W), NS = (N | S), NSW = (N | S | W), NW = (N | W),
	ES = (E | S), ESW = (E | S | W), EW = (E | W), SW = (S | W),
	NESW = (N | E | S | W),
	STEEP = 0b10000, STEEP_N = (STEEP | N), STEEP_E = (STEEP | E), STEEP_S = (STEEP | S), STEEP_W = (STEEP | W),
	INVALID = (STEEP_N | E | S | W)
};

enum TileType : unsigned char {
	DEFAULT = 0,
	GRASS = 1
};

class Tile {
private:
	TileType tile_type;
	Slope slope = FLAT;
	int height = 2;

public:
	Tile();

	Tile(TileType tile_typeTemp, Slope slopeTemp = FLAT, int heightTemp = 1);

	int getHeight() const { return height; }

	Slope getTileSlope() const { return slope; }
	bool updateSlope(unsigned char* cornerHeights);

	TileType getTileType() const { return tile_type; }

};


//GBTTD_TILE_H
