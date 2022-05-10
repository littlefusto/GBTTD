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
Vector3<Slope> getNeighbourDirections(Slope slope)
{
	slope = static_cast<Slope>(slope & NESW);
	Vector3<Slope> return_vec = Vector3<Slope>(FLAT, FLAT, FLAT);
	unsigned char shift = (slope | slope << 4);
	return_vec.x = (Slope) ((shift >> 3) & NESW);
	return_vec.y = (Slope) ((shift >> 1) & NESW);
	return_vec.z = (Slope) ((shift >> 2) & NESW);
	return return_vec;
}

bool Tile::registerSlopeChange(Slope to_add)
{
	//TODO handle MAX_MAP_HEIGHT case accurately
	if (height == MAX_MAP_HEIGHT)
	{
		registered_slope_change = INVALID;
		return false;
	}
	Vector3<Slope> neighbours = getNeighbourDirections(to_add);
	//Case: Two opposite directions are up already => STEEP
	if (slope == (neighbours.x | neighbours.y | to_add))
	{
		registered_slope_change = static_cast<Slope>(STEEP | to_add);
		return true;
	}
	//Case: Slope is STEEP
	if ((slope & STEEP) == STEEP)
	{
		//is only possible if we try to up the opposite direction of the tile
		if (to_add == getNeighbourDirections(slope).z)
		{
			registered_slope_change = static_cast<Slope>(slope ^ STEEP);
			return true;
		} else
		{
			registered_slope_change = INVALID;
			return false;
		}
	}
	//if this edge is already up we cant up it again
	if ((slope & to_add) == to_add)
	{
		registered_slope_change = INVALID;
		return false;
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
	//if the slope was steep before increase height by one
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
