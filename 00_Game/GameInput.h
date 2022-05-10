//
// Created by noop on 10.05.2022.
//
#pragma once

#include <gbttd.h>
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace GameInput {
	static Event event;

	static float moveRight, moveLeft, moveUp, moveDown;
	static Vector2f movement;
	static Vector2f oldMouse;
	static Vector2f click;

	static Clock RMBPressedTime;
	static int mousedrag;
	static bool RMBPressed;

	void init();

	void handleInput(Game*);
};