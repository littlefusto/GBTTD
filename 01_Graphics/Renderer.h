//
// Created by cpukiller on 06.05.22.
//

#ifndef GBTTD_RENDERER_H
#define GBTTD_RENDERER_H

#include <gbttd.h>

class Renderer
{
private:
	Map &map;
	sf::Texture map_texture;
	sf::Sprite map_sprite;
	sf::Image map_image;
	sf::Image* selected_tile_image; //TODO texture handler class
	sf::Vector2i point_at;
	sf::Vector2i selected_tile;
	sf::Vector2f pos;
public:
	Renderer(Map &map);

	bool generateMap();

	void renderMap(sf::RenderWindow &window);

	void getClickedTile(sf::Vector2i pos);
};


#endif //GBTTD_RENDERER_H
