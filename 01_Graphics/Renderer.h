//
// Created by cpukiller on 06.05.22.
//

#ifndef GBTTD_RENDERER_H
#define GBTTD_RENDERER_H

#include <SFML/Graphics/Sprite.hpp>
#include <gbttd.h>

#define CHUNK_SIZE 16

class Renderer
{
private:
	Map &map;
	std::vector<std::vector<RenderChunk* >> mapChunks;
	//sf::Sprite atlas;
	sf::Image* selectedTileImage;
	sf::Vector2i pointAt;
	sf::Vector2i selectedTile;
public:
	Renderer(Map &map);

	~Renderer();

	bool generateMap();

	void renderMap(sf::RenderWindow &window);

	vector<Tile*> getClickedTiles(sf::Vector2i pos);
};


#endif //GBTTD_RENDERER_H
