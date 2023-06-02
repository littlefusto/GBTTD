//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <gbttd.h>

#define CHUNK_SIZE 64

class Renderer
{
private:
	Map &map;
	std::vector<std::vector<RenderChunk* >> mapChunks;
	//sf::Sprite atlas;
	sf::Image* selectedTileImage;
	sf::Vector2i pointAt;
	sf::Vector2i selectedTile;

	sf::Vector2f mapToWorldPos(sf::Vector2f mapPos);
	sf::Vector2f worldToMapPos(sf::Vector2f worldPos);

public:
	Renderer(Map &map);

	~Renderer();

	bool generateMap();
	void updateMap();
	void updateRect(int x, int y, int width, int height);

	void renderMap(sf::RenderWindow &window);

	sf::Vector2i getClickedTile(sf::Vector2f worldPos);

	sf::Vector2i getClickedVertex(sf::Vector2f worldPos);
};
