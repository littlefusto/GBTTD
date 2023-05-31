//
// Created by cpukiller on 06.05.22.
//

#include "TextureHandler.h"
#include "Tile.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <gbttd.h>
#include <cmath>

Renderer::Renderer(Map &map) : map(map)
{
	pointAt = sf::Vector2i(0, 0);
	selectedTile = sf::Vector2i(-1, -1);
	selectedTileImage = TextureHandler::getInstance()->getImage("selectedTile.png");
	mapChunks = std::vector<std::vector<RenderChunk*>>((int) ceil(map.getSize().y / CHUNK_SIZE));
	for (int y = 0; y < mapChunks.size(); y++) {
		mapChunks[y] = std::vector<RenderChunk*>((int) ceil(map.getSize().x / CHUNK_SIZE));
		for (int x = 0; x < mapChunks[y].size(); x++) {
			mapChunks[y][x] = nullptr;
		}
	}
	//atlas = sf::Sprite(*TextureHandler::getInstance()->getTextureAtlas());
	//atlas.setPosition(0,0);
	printf("Renderer init complete\n");
}

Renderer::~Renderer() {
	for (int y = 0; y < map.getSize().y; y++) {
		for (int x = 0; x < map.getSize().x; x++) {
			delete mapChunks[y][x];
		}
	}
	mapChunks.clear();
}

bool Renderer::generateMap()
{
	std::vector<std::vector<Tile*>> &content = map.getContent();
	TextureHandler *textureHandler = TextureHandler::getInstance();
	Vector2i renderChunkSize(CHUNK_SIZE * TILE_WIDTH, CHUNK_SIZE * TILE_HEIGHT);

	for (int y = 0; y < mapChunks.size(); y++) {
		int px = -y * renderChunkSize.x / 2;
		int py = y * renderChunkSize.y / 2;
		for (int x = 0; x < mapChunks[y].size(); x++) {
			mapChunks[y][x] = new RenderChunk(map, x, y);
			mapChunks[y][x]->setPosition(px, py);
			px += renderChunkSize.x / 2;
			py += renderChunkSize.y / 2;
		}
	}
	printf("Generated Chunks.\n");
	return true;
}

double calculateDistance(Vector2i &a, Vector2i &b)
{
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

int calculateSquaredDistance(Vector2i &a, Vector2i &b)
{
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	return dx * dx + dy * dy;
}

//Returns 4 Tiles in clockwise order around a vertex/their intersection point
vector<Tile*> Renderer::getClickedTiles(sf::Vector2i pos)
{
	vector<Tile*> clicked_tiles = {nullptr,nullptr,nullptr,nullptr};
	vector<vector<Tile*>> &content = map.getContent();
	for (int i = 0; i < map.getSize().x; i++)
	{
		for (int j = 0; j < map.getSize().y; j++)
		{
			//right and down for every i
			//left and down for every j
			//rest is adjusting
			int x = (TILE_WIDTH / 2 * i) - (TILE_WIDTH / 2 * j) - TILE_WIDTH / 2;
			int y = (TILE_HEIGHT / 2 * i) + (TILE_HEIGHT / 2 * j) - 8 * content[j][i]->getHeight() - TILE_HEIGHT;
			textureInfo& texture_info = TextureHandler::getInstance()->getTextureByTileType(content[j][i]);
			sf::Image* source = texture_info.image;
			if (source == nullptr)
			{
				std::cerr << "Tile at x:" << i << " y:" << j << " has invalid type or slope" << std::endl;
			} else
			{
				Vector2i pixel_pos = Vector2i(pos.x - x,pos.y - y);
				if (pixel_pos.x <= source->getSize().x && pixel_pos.x >= 0 && pixel_pos.y <= source->getSize().y && pixel_pos.y >= 0 &&
					source->getPixel(pixel_pos.x, pixel_pos.y).a > 0)
				{
					/* Selected Tile not needed atm
					 * selectedTile = Vector2i(x, y);
					selectedTileImage->create(source->getSize().x, source->getSize().y);
					selectedTileImage->copy(*source, 0, 0);
					selectedTileImage->createMaskFromColor(Color(0, 255, 0), 200);*/
					int32_t smallest_distance = INT32_MAX;
					int n = calculateSquaredDistance(pixel_pos,texture_info.maxNorthPixel);
					int e = calculateSquaredDistance(pixel_pos,texture_info.maxEastPixel);
					int s = calculateSquaredDistance(pixel_pos,texture_info.maxSouthPixel);
					int w = calculateSquaredDistance(pixel_pos,texture_info.maxWestPixel);
					smallest_distance = min(min(n,e),min(s,w));
					if(smallest_distance == n) {
						pointAt = Vector2i(x,y) + texture_info.maxNorthPixel;
						clicked_tiles = {map.getTile(i-1,j-1),map.getTile(i,j-1),map.getTile(i,j),map.getTile(i-1,j)};
					} else if(smallest_distance == e) {
						pointAt = Vector2i(x,y) + texture_info.maxEastPixel;
						clicked_tiles = {map.getTile(i,j-1),map.getTile(i+1,j-1),map.getTile(i+1,j),map.getTile(i,j)};
					} else if(smallest_distance == s) {
						pointAt = Vector2i(x,y) + texture_info.maxSouthPixel;
						clicked_tiles = {map.getTile(i,j),map.getTile(i+1,j),map.getTile(i+1,j+1),map.getTile(i,j+1)};
					} else if(smallest_distance == w) {
						pointAt = Vector2i(x,y) + texture_info.maxWestPixel;
						clicked_tiles = {map.getTile(i-1,j),map.getTile(i,j),map.getTile(i,j+1),map.getTile(i-1,j+1)};
					}
				}
			}
		}
	}
	generateMap();
	return clicked_tiles;
}

void Renderer::renderMap(sf::RenderWindow &window)
{
	window.clear();
	for (int y = 0; y < mapChunks.size(); y++) {
		for (int x = 0; x < mapChunks[y].size(); x++) {
			window.draw(*mapChunks[y][x]);
		}
	}
	// window.draw(atlas);
	window.display();
}

/**
* Calculates the area of the parallelogram of the three points.
* This is actually the same as the area of the triangle defined by the three points, multiplied by 2.
* @return 2 * triangleArea(a,b,c)
*/
int perpDotProduct(sf::Vector2i a, sf::Vector2i b, sf::Vector2i c)
{
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}
/*
void Renderer::getClickedTile(sf::Vector2i pos)
{
	//Using the perp dot product to determine if the clicked point is above or below a line
	//Considered lines are along the edges of the tiles
	//TODO: Alternative: calculate the distance of the clicked point from one edge of the map
	//and divide it by the diagonal of one tile
	//First we consider lines running from left to right starting with the tile at the top
	int lastRun = 1;
	int this_run = 12;
	int y = -1;
	for (int i = 0; i <= map.getSize().x; i++)
	{
		sf::Vector2i v1 = { map.getSize().x / 2 * TILE_WIDTH - i * TILE_WIDTH / 2, i * TILE_HEIGHT / 2 };
		sf::Vector2i v2 = {
				map.getSize().x * TILE_WIDTH - i * TILE_WIDTH / 2, map.getSize().y / 2 * TILE_HEIGHT + i * TILE_HEIGHT / 2
		};
		int pdp = perpDotProduct(v1, v2, pos);
		this_run = (pdp > 0) ? 1 : -1;
		//printf("v1:%d %d v2: %d %d point: %d %d pdp=%d\n",v1.x,v1.y,v2.x,v2.y,pointAt.x, pointAt.y,pdp);
		if (lastRun == 1 && this_run == -1)
		{
			y = i - 1;
		}
		lastRun = this_run;
	}
	//Then we consider lines running from right to left starting with the tile at the top
	int x = -1;
	lastRun = 1;
	this_run = 12;
	for (int i = 0; i <= map.getSize().x; i++)
	{
		sf::Vector2i v1 = { map.getSize().x / 2 * TILE_WIDTH + i * TILE_WIDTH / 2, i * TILE_HEIGHT / 2 };
		sf::Vector2i v2 = { i * TILE_WIDTH / 2, map.getSize().y / 2 * TILE_HEIGHT + i * TILE_HEIGHT / 2 };
		int pdp = perpDotProduct(v1, v2, pos);
		this_run = (pdp < 0) ? 1 : -1;
		//printf("v1:%d %d v2: %d %d point: %d %d pdp=%d\n",v1.x,v1.y,v2.x,v2.y,pointAt.x, pointAt.y,pdp);
		if (lastRun == 1 && this_run == -1)
		{
			x = i - 1;
		}
		lastRun = this_run;
	}

	if (x >= 0 && y >= 0)
	{
		selectedTile.x = x;
		selectedTile.y = y;
		generateMap();
	}
}*/