//
// Created by cpukiller on 06.05.22.
//

#include <gbttd.h>

Map::Map(int width, int height){
	this->x = width;
	this->y = height;
	this->tiles.resize(height);
	this->heightMap.resize(height + 1);
	for (int i = 0; i < height; i++) {
		this->tiles[i].resize(width);
		this->heightMap[i].resize(width + 1);
		for (int j = 0; j < width; j++)	{
			this->tiles[i][j] = new Tile(1, GRASS, FLAT);
			this->heightMap[i][j] = 1;
		}
		heightMap[i][width] = 1;
	}
	this->heightMap[height].resize(width + 1);
	for (int i = 0; i <= width; i++) {
		heightMap[height][i] = 1;
	}
}

Map::~Map(){
	for (int i = 0; i < this->y; i++) {
		for (int j = 0; j < this->x; j++) {
			free(tiles[i][j]);
		}
	}
	tiles.clear();
	heightMap.clear();
}

void Map::fillMap(vector<vector<TileType>> &map) {
	map.resize(x);
	for (int w = 0; w < this->x; w++)
	{
		map[w].resize(y);
		for (int h = 0; h < this->y; h++)
		{
			map[w][h] = TileType::GRASS;
		}
	}
}

Tile* Map::getTile(int x, int y) {
	if (x<0 || x >= this->x || y < 0 || y >= this->y) return nullptr;
	return tiles[y][x];
}

Vector2i Map::getSize() {
	Vector2i vector(this->x, this->y);
	return vector;
}

unsigned char* Map::getTileHeights(int x, int y) {
	return new unsigned char[4]{heightMap[y][x], heightMap[y][x+1], heightMap[y+1][x+1], heightMap[y+1][x]};
}

// !!!!!!!!!!!!!!!!
// TODO: Rewrite without recursion -> fine for 16 but slow for 25+ height
bool Map::raiseHeight(int x, int y) {
	if (!canRaise(x, y)) return false;
	int maxD = heightMap[y][x];
	raiseVertex(x, y);
	updateSlopesRect(x - maxD - 1, y - maxD - 1, maxD*2+2, maxD*2+2);
	return true;
}

// !!!!!!!!!!!!!!!!
// TODO: Rewrite without recursion -> fine for 16 but slow for 25+ height
bool Map::lowerHeight(int x, int y) {
	if (!canLower(x, y)) return false;
	int maxD = MAX_MAP_HEIGHT - heightMap[y][x];
	lowerVertex(x, y);
	updateSlopesRect(x - maxD - 1, y - maxD - 1, maxD*2+2, maxD*2+2);
	return true;
}

void Map::raiseVertex(int x, int y) {
	if (x > 0 && heightMap[y][x] > heightMap[y][x - 1]) raiseVertex(x - 1, y);
	if (y > 0 && heightMap[y][x] > heightMap[y - 1][x]) raiseVertex(x, y - 1);
	if (x < this->x && heightMap[y][x] > heightMap[y][x + 1]) raiseVertex(x + 1, y);
	if (y < this->y && heightMap[y][x] > heightMap[y + 1][x]) raiseVertex(x, y + 1);
	heightMap[y][x]++;
}

void Map::lowerVertex(int x, int y) {
	if (x > 0 && heightMap[y][x] < heightMap[y][x - 1]) lowerVertex(x - 1, y);
	if (y > 0 && heightMap[y][x] < heightMap[y - 1][x]) lowerVertex(x, y - 1);
	if (x < this->x && heightMap[y][x] < heightMap[y][x + 1]) lowerVertex(x + 1, y);
	if (y < this->y && heightMap[y][x] < heightMap[y + 1][x]) lowerVertex(x, y + 1);
	heightMap[y][x]--;
}

bool Map::canRaise(int x, int y) {
	if (heightMap[y][x] == MAX_MAP_HEIGHT) return false;
	if (hasBuilding(x, y) || hasBuilding(x-1, y) || hasBuilding(x, y-1) || hasBuilding(x-1, y-1)) return false;
	if (x > 0 && heightMap[y][x] > heightMap[y][x - 1] && !canRaise(x - 1, y)) return false;
	if (y > 0 && heightMap[y][x] > heightMap[y - 1][x] && !canRaise(x, y - 1)) return false;
	if (x < this->x && heightMap[y][x] > heightMap[y][x + 1] && !canRaise(x + 1, y)) return false;
	if (y < this->y && heightMap[y][x] > heightMap[y + 1][x] && !canRaise(x, y + 1)) return false;
	return true;
}

bool Map::canLower(int x, int y) {
	if (heightMap[y][x] == 0) return false;
	if (x > 0 && heightMap[y][x] < heightMap[y][x - 1] && !canLower(x - 1, y)) return false;
	if (y > 0 && heightMap[y][x] < heightMap[y - 1][x] && !canLower(x, y - 1)) return false;
	if (x < this->x && heightMap[y][x] < heightMap[y][x + 1] && !canLower(x + 1, y)) return false;
	if (y < this->y && heightMap[y][x] < heightMap[y + 1][x] && !canLower(x, y + 1)) return false;
	return true;
}

bool Map::hasBuilding(int x, int y) {
	if (x < 0 || x >= this->x || y < 0 || y >= this->y) return false;
	return false;
}

void Map::updateSlopesRect(int x, int y, unsigned int width, unsigned int height) {
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x + width > this->x) width = this->x - x;
	if (y + height > this->y) height = this->y - y;
	if (width <= 0 || height <= 0) return;
	unsigned char corners[4] = {0,0,0,0};
	for (int ty = y; ty < y + height; ty++) {
		for (int tx = x; tx < x + width; tx++) {
			corners[0] = heightMap[ty][tx];
			corners[1] = heightMap[ty][tx + 1];
			corners[2] = heightMap[ty + 1][tx + 1];
			corners[3] = heightMap[ty + 1][tx];
			tiles[ty][tx]->updateSlope(corners);
		}
	}
}

void Map::updateSlopes() {
	updateSlopesRect(0, 0, this->x, this->y);
}