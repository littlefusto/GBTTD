//
// Created by cpukiller on 06.05.22.
//

#pragma once

#include <gbttd.h>

#define CHUNK_SIZE 16

#ifdef __linux__
#define BASE_FONT "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc" // change to installed font, don't know which font should be present on all linux systems
#elif _WIN32
#define BASE_FONT "C:\\Windows\\Fonts\\Arial.ttf" // this should work
#endif

class Renderer
{
private:
	Map* map;
	std::vector<std::vector<RenderChunk* >> mapChunks;
	//sf::Sprite atlas;
	sf::Image* selectedTileImage;
	sf::Vector2i pointAt;
	sf::Vector2i selectedTile;

	sf::Font defaultFont;
	sf::Clock frametimeClock;
	sf::Text fpsText;

	sf::Vector2f mapToWorldPos(sf::Vector2f mapPos);
	sf::Vector2f worldToMapPos(sf::Vector2f worldPos);

	void deleteChunks();

public:
	Renderer(Map* map);

	~Renderer();

	bool generateMap();
	void updateMap();
	void updateRect(int x, int y, int width, int height);

	void renderMap(sf::RenderWindow &window);

	sf::Vector2i getClickedTile(sf::Vector2f worldPos);

	sf::Vector2i getClickedVertex(sf::Vector2f worldPos);

	void setMap(Map* map);

};
