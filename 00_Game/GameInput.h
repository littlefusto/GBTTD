//
// Created by noop on 10.05.2022.
//
#pragma once

#include <gbttd.h>
#include <SFML/Graphics.hpp>
#include <Game.h>

namespace GameInput {
	static Event event;

	static float moveRight, moveLeft, moveUp, moveDown;
	static Vector2f movement;
	static Vector2f oldMouse;
	static Vector2f click;
	
	static Vector2u oldWindowSize = Vector2u(WINDOW_SIZE_X, WINDOW_SIZE_Y);

	static bool MMBPressed = false;

	void init();

	void handleInput(Game*);
	void handleMenuEvent(Game*, sf::Event&);
	void handleBuildEvent(Game*, sf::Event&);
	void handleMapEvent(Game*, sf::Event&);
};