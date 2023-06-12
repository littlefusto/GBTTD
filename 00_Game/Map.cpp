//
// Created by cpukiller on 06.05.22.
//

#include <gbttd.h>

Map::Map(int width, int height){
	this->x = width;
	this->y = height;
	this->tiles = std::vector<std::vector<Tile*>>(height);
	this->heightMap = std::vector<std::vector<unsigned char>>(height + 1);
	for (int i = 0; i < height; i++) {
		this->tiles[i] = std::vector<Tile*>(width);
		this->heightMap[i] = std::vector<unsigned char>(width + 1);
		for (int j = 0; j < width; j++)	{
			this->tiles[i][j] = new Tile(GRASS, FLAT, 1);
			this->heightMap[i][j] = 1;
		}
		heightMap[i][width] = 1;
	}
	this->heightMap[height] = std::vector<unsigned char>(width + 1);
	for (int i = 0; i <= width; i++) {
		heightMap[height][i] = 1;
	}
}

Map::~Map(){
	for (int i = 0; i < this->y; i++) {
		for (int j = 0; j < this->x; j++) {
			delete tiles[i][j];
		}
	}
	tiles.clear();
	heightMap.clear();
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

bool Map::raiseHeight(int x, int y) {
	if (!canRaise(x, y)) return false;
	int maxD = heightMap[y][x];
	raiseVertex(x, y);
	// TODO updating of slopes and tile heights seems to be bugged at the edges when raising from height 0
	updateSlopesRect(x - maxD - 1, y - maxD - 1, maxD*2+2, maxD*2+2);
	return true;
}

bool Map::lowerHeight(int x, int y) {
	if (!canLower(x, y)) return false;
	int maxD = MAX_MAP_HEIGHT - heightMap[y][x];
	lowerVertex(x, y);
	updateSlopesRect(x - maxD - 1, y - maxD - 1, maxD*2+2, maxD*2+2);
	return true;
}

void Map::raiseVertex(int x, int y) {
	char tileHeight = heightMap[y][x];
	heightMap[y][x]++;
	for (char i = 1; i <= tileHeight; i++) {
		char minHeight = tileHeight - i + 1;
		for (char k = 0; k <= i; k++) {
			if (minHeight <= 0) break;
			// top right
			if (y - i >= 0) {
				if (x - k >= 0 && heightMap[y - i][x - k] < minHeight) heightMap[y - i][x - k] = minHeight;
				if (x + k <= this->x && heightMap[y - i][x + k] < minHeight) heightMap[y - i][x + k] = minHeight;
			}
			// bottom right
			if (x + i <= this->x) {
				if (y - k >= 0 && heightMap[y - k][x + i] < minHeight) heightMap[y - k][x + i] = minHeight;
				if (y + k <= this->y && heightMap[y + k][x + i] < minHeight) heightMap[y + k][x + i] = minHeight;
			}
			// bottom left
			if (y + i <= this->y) {
				if (x - k >= 0 && heightMap[y + i][x - k] < minHeight) heightMap[y + i][x - k] = minHeight;
				if (x + k <= this->x && heightMap[y + i][x + k] < minHeight) heightMap[y + i][x + k] = minHeight;
			}
			// top left
			if (x - i >= 0) {
				if (y - k >= 0 && heightMap[y - k][x - i] < minHeight) heightMap[y - k][x - i] = minHeight;
				if (y + k <= this->y && heightMap[y + k][x - i] < minHeight) heightMap[y + k][x - i] = minHeight;
			}
			minHeight--;
		}
	}
}

void Map::lowerVertex(int x, int y) {
	char tileHeight = heightMap[y][x];
	heightMap[y][x]--;
	for (char i = 1; i <= MAX_MAP_HEIGHT - tileHeight; i++) {
		char maxHeight = tileHeight + i - 1;
		for (char k = 0; k <= i; k++) {
			if (maxHeight >= MAX_MAP_HEIGHT) break;
			// top right
			if (y - i >= 0) {
				if (x - k >= 0 && heightMap[y - i][x - k] > maxHeight) heightMap[y - i][x - k] = maxHeight;
				if (x + k <= this->x && heightMap[y - i][x + k] > maxHeight) heightMap[y - i][x + k] = maxHeight;
			}
			// bottom right
			if (x + i <= this->x) {
				if (y - k >= 0 && heightMap[y - k][x + i] > maxHeight) heightMap[y - k][x + i] = maxHeight;
				if (y + k <= this->y && heightMap[y + k][x + i] > maxHeight) heightMap[y + k][x + i] = maxHeight;
			}
			// bottom left
			if (y + i <= this->y) {
				if (x - k >= 0 && heightMap[y + i][x - k] > maxHeight) heightMap[y + i][x - k] = maxHeight;
				if (x + k <= this->x && heightMap[y + i][x + k] > maxHeight) heightMap[y + i][x + k] = maxHeight;
			}
			// top left
			if (x - i >= 0) {
				if (y - k >= 0 && heightMap[y - k][x - i] > maxHeight) heightMap[y - k][x - i] = maxHeight;
				if (y + k <= this->y && heightMap[y + k][x - i] > maxHeight) heightMap[y + k][x - i] = maxHeight;
			}
			maxHeight++;
		}
	}
}

bool Map::canRaise(int x, int y) {
	char tileHeight = heightMap[y][x];
	if (tileHeight == MAX_MAP_HEIGHT) return false;
	if (hasBuilding(x, y) || hasBuilding(x-1, y) || hasBuilding(x, y-1) || hasBuilding(x-1, y-1)) return false;
	// check squares of increasing size around the center
	for (char i = 1; i <= heightMap[y][x]; i++) {
		char minHeight = tileHeight - i + 1;
		for (char k = 0; k <= i; k++) {
			// top right
			if (y - i > 0 && x - k >= 0 && x + k < this->x && ((heightMap[y - i][x - k] < minHeight && hasBuilding(x-k, y-i-1)) || (k < i && heightMap[y - i][x + k] < minHeight && hasBuilding(x+k, y-i-1)))) return false;
			// bottom right
			if (x + i < this->x && y - k >= 0 && y + k < this->y && ((heightMap[y - k][x + i] < minHeight && hasBuilding(x+i, y-k)) || (k < i && heightMap[y + k][x + i] < minHeight && hasBuilding(x+i, y+k)))) return false;
			// bottom left
			if (y + i < this->y && x - k >= 0 && x + k < this->x && ((heightMap[y + i][x - k] < minHeight && hasBuilding(x-k, y+i)) || (k < i && heightMap[y + i][x + k] < minHeight && hasBuilding(x+k, y+i)))) return false;
			// top left
			if (x - i > 0 && y - k >= 0 && y + k < this->y && ((heightMap[y - k][x - i] < minHeight && hasBuilding(x-i-1, y-k)) || (k < i && heightMap[y + k][x - i] < minHeight && hasBuilding(x-i-1, y+k)))) return false;
			minHeight--;
		}
		// check corners because the diagonal tiles need to be modified as well
		minHeight = tileHeight - i * 2 + 1;
		if (y - i > 0 && x - i > 0 && x + i < this->x && y + i < this->y && (
			(heightMap[y - i][x - i] < minHeight && hasBuilding(x-i-1, y-i-1)) 	// top
			|| (heightMap[y + i][x - i] < minHeight && hasBuilding(x+i, y-i-1)) 	// right
			|| (heightMap[y + i][x + i] < minHeight && hasBuilding(x+i, y+i)) 	// bottom
			|| (heightMap[y - i][x + i] < minHeight && hasBuilding(x-i-1, y+i)))) // left
		{
			return false;
		}
	}
	return true;
}

bool Map::canLower(int x, int y) {
	char tileHeight = heightMap[y][x];
	if (tileHeight == 0) return false;
	if (hasBuilding(x, y) || hasBuilding(x-1, y) || hasBuilding(x, y-1) || hasBuilding(x-1, y-1)) return false;
	// check squares of increasing size around the center
	for (char i = 1; i <= MAX_MAP_HEIGHT-heightMap[y][x]; i++) {
		char maxHeight = tileHeight + i - 1;
		for (char k = 0; k <= i; k++) {
			// top right
			if (y - i > 0 && x - k >= 0 && x + k < this->x && ((heightMap[y - i][x - k] > maxHeight && hasBuilding(x-k, y-i-1)) || (k < i && heightMap[y - i][x + k] > maxHeight && hasBuilding(x+k, y-i-1)))) return false;
			// bottom right
			if (x + i < this->x && y - k >= 0 && y + k < this->y && ((heightMap[y - k][x + i] > maxHeight && hasBuilding(x+i, y-k)) || (k < i && heightMap[y + k][x + i] > maxHeight && hasBuilding(x+i, y+k)))) return false;
			// bottom left
			if (y + i < this->y && x - k >= 0 && x + k < this->x && ((heightMap[y + i][x - k] > maxHeight && hasBuilding(x-k, y+i)) || (k < i && heightMap[y + i][x + k] > maxHeight && hasBuilding(x+k, y+i)))) return false;
			// top left
			if (x - i > 0 && y - k >= 0 && y + k < this->y && ((heightMap[y - k][x - i] > maxHeight && hasBuilding(x-i-1, y-k)) || (k < i && heightMap[y - k][x - i] > maxHeight && hasBuilding(x-i-1, y+k)))) return false;
			maxHeight++;
		}
		// check corners because the diagonal tiles need to be modified as well
		maxHeight = tileHeight + i * 2 - 1;
		if (y - i > 0 && x - i > 0 && x + i < this->x && y + i < this->y && (
			(heightMap[y - i][x - i] > maxHeight && hasBuilding(x-i-1, y-i-1)) 	// top
			|| (heightMap[y + i][x - i] > maxHeight && hasBuilding(x+i, y-i-1)) 	// right
			|| (heightMap[y + i][x + i] > maxHeight && hasBuilding(x+i, y+i)) 	// bottom
			|| (heightMap[y - i][x + i] > maxHeight && hasBuilding(x-i-1, y+i)))) // left
		{
			return false;
		}
	}
	return true;
}

bool Map::hasBuilding(int x, int y) {
	if (x < 0 || x >= this->x || y < 0 || y >= this->y) return false;
	// For now always return false.
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