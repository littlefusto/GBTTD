//
// Created by noop on 08.05.2022.
//
#include <JSONMapLoader.h>
#include <gbttd.h>

void Game::init()
{
	window = new RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "GBTTD");
	view = new View(sf::FloatRect(0.f, 0.f, WINDOW_SIZE_X, WINDOW_SIZE_Y));
	view->setViewport(sf::FloatRect(0,0,1,1)); // can be used later to allow for multiple view ports in the gui similar to the real game

	window->setView(*view);
	std::string path = "map1";
	//map = JSONMapLoader::loadMap(path);
	map = new Map(512, 512);
	renderer = new Renderer(*map);
	renderer->generateMap();

	GameInput::init();
}

void Game::poll()
{
	GameInput::handleInput(this);
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

RenderWindow* Game::getWindow() const
{
	return window;
}

Map* Game::getMap() const
{
	return map;
}

GameState Game::getGameState() const
{
	return gameState;
}

void Game::setGameState(GameState gameState)
{
	Game::gameState = gameState;
}

void Game::setMap(Map* map)
{
	Game::map = map;
}

Renderer* Game::getRenderer() const
{
	return renderer;
}

View* Game::getView() const
{
	return view;
}

void Game::setView(View* view)
{
	Game::view = view;
}
