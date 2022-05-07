//
// Created by cpukiller on 06.05.22.
//

#ifndef GBTTD_RENDERER_H
#define GBTTD_RENDERER_H

#include <Map.h>
#include <SFML/Graphics.hpp>

struct CameraContext
{
	float zoom{};
	sf::Vector2f camera_pos;
};

class Renderer
{
private:
	Map &map;
	sf::Texture map_texture;
	sf::Sprite map_sprite;
	sf::Vector2i point_at;
	sf::Vector2i selected_tile;
	sf::Vector2f pos;
public:
	Renderer(Map &map);

	bool generateMap();

	void renderMap(sf::RenderWindow &window, CameraContext &context);

	Tile* getClickedTile(sf::Vector2i pos, CameraContext &context);
};


#endif //GBTTD_RENDERER_H
