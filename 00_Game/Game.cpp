//
// Created by noop on 08.05.2022.
//
#include <JSONMapLoader.h>
#include <gbttd.h>
#include "Game.h"

void Game::init()
{
	window = new RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "GBTTD");
	view = new View(sf::FloatRect(0.f, 0.f, WINDOW_SIZE_X, WINDOW_SIZE_Y));

	window->setView(*view);
	std::string path = "map1";
	map = JSONMapLoader::loadMap(path);
	renderer = new Renderer(*map);
	renderer->generateMap();
}

void Game::poll()
{
	handleInput();
	view->move(movement);
	window->setView(*view);
	if (!window->isOpen()) shouldClose = true;
}

void Game::loop()
{
}

void Game::draw()
{
	renderer->renderMap(*window);
}

void Game::cleanup()
{
	delete window;
	delete map;
	delete view;
	delete renderer;
	delete mapLoader;
	window = nullptr;
	map = nullptr;
	view = nullptr;
	renderer = nullptr;
	mapLoader = nullptr;
}

void Game::run()
{
	init();
	while (!shouldClose)
	{
		poll();
		loop();
		draw();
	}
	cleanup();
}
