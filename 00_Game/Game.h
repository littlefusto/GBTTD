//
// Created by noop on 07.05.2022.
//
#pragma once

#include <gbttd.h>

enum game_state
{
	state_menu = 0,
	state_map = 1
};

struct Game
{
private:
	sf::RenderWindow* window = nullptr;
	Map* map = nullptr;
	MapLoader* mapLoader = nullptr;
	Renderer* renderer = nullptr;

	CameraContext context{ .zoom = 2.0, .camera_pos = Vector2f{ 0.0, 0.0 }};
	Vector2f movement{ 0.0, 0.0 };
	Vector2f oldMouse{ 0.0, 0.0 };

	game_state gameState = state_map;
	sf::Event event{};

	bool RMBPressed = false;
	bool shouldClose = false;

	void init();

	void poll();

	void loop();

	void draw();

	void cleanup();

public:
	void run();
};
//GBTTD_GAME_H
