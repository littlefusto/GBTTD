//
// Created by fusto on 06.05.22.
//

#include <gbttd.h>
#include "Tile.h"


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

void Tile::addToHeight(int to_add)
{
	height += to_add;
	if (height > MAX_MAP_HEIGHT)
	{
		height = MAX_MAP_HEIGHT;
	}
}

//x = clockwise left
//y = clockwise right
//z = opposite
Vector3<Slope> getNearSlopes(Slope slope)
{
	slope = static_cast<Slope>(slope & NESW);
	Vector3<Slope> return_vec = Vector3<Slope>(FLAT, FLAT, FLAT);
	if (slope == N) return_vec.x = W; else return_vec.x = static_cast<Slope>(slope << 1);
	if (slope == W) return_vec.y = N; else return_vec.y = static_cast<Slope>(slope >> 1);
	return_vec.z = static_cast<Slope>(NESW & ~(return_vec.x | return_vec.y | slope));
	return return_vec;
}

bool Tile::registerSlopeChange(Slope to_add)
{
	if (height == MAX_MAP_HEIGHT)
	{
		registered_slope_change = INVALID;
		return false;
	}
	Vector3<Slope> neighbours = getNearSlopes(to_add);
	if (slope == (neighbours.x | neighbours.y | to_add))
	{
		registered_slope_change = static_cast<Slope>(STEEP | to_add);
		return true;
	}
	if ((slope & STEEP) == STEEP)
	{
		if (to_add == getNearSlopes(slope).z)
		{
			registered_slope_change = static_cast<Slope>(slope ^ STEEP);
			return true;
		} else
		{
			registered_slope_change = INVALID;
			return false;
		}
	}
	if ((slope & to_add) == to_add)
	{
		registered_slope_change = INVALID;
		return false;
	}
	if (slope == FLAT || slope == neighbours.x || slope == neighbours.y || slope == (NESW & ~to_add) ||
		slope == neighbours.z)
	{
	}
	registered_slope_change = (Slope) (slope | to_add);
	return true;
}

bool Tile::commitSlopeChange()
{
	if (registered_slope_change == INVALID) return false;
	if (height == MAX_MAP_HEIGHT)
	{
		slope = FLAT;
		return false;
	}
	if ((slope & STEEP) == STEEP && (registered_slope_change & STEEP) == 0) addToHeight(1);
	slope = registered_slope_change;
	if (slope == NESW)
	{
		//All edges where pushed up; increase height
		slope = FLAT;
		addToHeight(1);
	}
	return true;
}

Tile::Tile()
= default;
