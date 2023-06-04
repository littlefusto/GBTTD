//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <gbttd.h>

#define MAX_MAP_HEIGHT 32 // real game has 30

using namespace std;

class Map
{
private:
	int x = 6;
	int y = 6;
	std::vector<std::vector<unsigned char>> heightMap;
	vector<vector<Tile*>> tiles;

	// returns true if there is a building on top of the specified tile
	bool hasBuilding(int x, int y);

	// recursively test if it is possible to raise or lower the vertex
	bool canRaise(int x, int y);
	bool canLower(int x, int y);

	// executes raising or lowering without performing check
	void raiseVertex(int x, int y);
	void lowerVertex(int x, int y);

	// Update the slopes of tile in the specified area/ the complete map
	void updateSlopesRect(int x, int y, unsigned int width, unsigned int height);
	void updateSlopes();

public:

	Map(int width, int height);
	~Map();

	void fillMap(vector<vector<TileType>> &map);

	Vector2<int> getSize();

	vector<vector<Tile*>> &getContent() { return tiles; }
	vector<vector<unsigned char>> &getHeightMap() { return heightMap; }

	// returns a pointer to the tile at the specified position
	Tile* getTile(int x, int y);

	// returns the heights of the corners of the tile
	unsigned char* getTileHeights(int x, int y);

	// returns the height of a specific vertex
	inline unsigned char getHeight(int x, int y) { return heightMap[y][x]; }

	// raise the height of the specified vertex and all neighbouring vertices that need to be raised to achieve this
	// returns true if the action was succesful
	bool raiseHeight(int x, int y);

	// lower the height of the specified vertex and all neighbouring vertices that need to be lowered to achieve this
	// returns true if the action was succesful
	bool lowerHeight(int x, int y);

};
