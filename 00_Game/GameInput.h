//
// Created by noop on 10.05.2022.
//
#pragma once

#include <gbttd.h>
#include <SFML/Graphics.hpp>
#include "Game.h"

struct GameInput
{
private:
	static Event event;

	static float moveRight, moveLeft, moveUp, moveDown;
	static Vector2f movement;
	static Vector2f oldMouse;

	static bool RMBPressed;
	static bool mouseWasMoved;
public:
	static void init();
	static void handleInput(Game*);
};