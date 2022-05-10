//
// Created by noop on 07.05.2022.
//
#pragma once

#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720

#include <gbttd.h>
#include <GameInput.h>

enum game_state
{
	state_menu = 0,
	state_map = 1,
	state_build = 2
};

struct Game
{
private:
	sf::RenderWindow* window = nullptr;
	sf::View* view = nullptr;

	Map* map = nullptr;

	MapLoader* mapLoader = nullptr;
	Renderer* renderer = nullptr;

	game_state gameState = state_map;
public:
	void setGameState(game_state gameState);

	View* getView() const;

	void setView(View* view);

	void setMap(Map* map);

	Renderer* getRenderer() const;

	RenderWindow* getWindow() const;

	Map* getMap() const;

	game_state getGameState() const;

private:

	bool RMBPressed = false;
	bool mouseWasMoved = false;
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
