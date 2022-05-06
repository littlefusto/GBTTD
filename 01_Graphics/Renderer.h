//
// Created by tscharn on 06.05.22.
//
#pragma once

#include "00_Game/Map.h"
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
public:
	Renderer(Map &map);

	bool generateMap();

	void renderMap(sf::RenderWindow &window, CameraContext &context);
};


//GBTTD_RENDERER_H
