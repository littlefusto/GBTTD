//
// Created by noop on 08.05.2022.
//
#include <gbttd.h>
#include "Game.h"


void Game::init()
{
	window = new RenderWindow(sf::VideoMode(1280, 720), "GBTTD");
	map = new Map();
	renderer = new Renderer(*map);
	mapLoader = new MapLoader();
}

void Game::poll()
{
	while (window->pollEvent(event))
	{
		switch (gameState)
		{
		case state_menu:
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) { gameState = state_map; }
				break;
			case sf::Event::Closed:
				window->close();
				break;
			default:
				break;
			}
			break;
		case state_map:
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.delta > 0.0f)
				{
					context.zoom *= 1.1;
				} else
				{
					context.zoom /= 1.1;
				}
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					movement.x += 0.1f;
					break;
				case sf::Keyboard::Right:
					movement.x += -0.1f;
					break;
				case sf::Keyboard::Up:
					movement.y += 0.1f;
					break;
				case sf::Keyboard::Down:
					movement.y += -0.1f;
					break;
				case sf::Keyboard::Escape:
					gameState = state_menu;
					break;
				default:
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					movement.x += -0.1f;
					break;
				case sf::Keyboard::Right:
					movement.x += 0.1f;
					break;
				case sf::Keyboard::Up:
					movement.y += -0.1f;
					break;
				case sf::Keyboard::Down:
					movement.y += 0.1f;
					break;
				default:
					break;
				}
				break;
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					RMBPressed = true;
				} else if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i pos;
					pos.x = event.mouseButton.x;
					pos.y = event.mouseButton.y;
					renderer->getClickedTile(pos, context);
				}
				break;
			case Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					RMBPressed = false;
				}
				break;
			case Event::MouseMoved:
				if (RMBPressed)
				{
					context.camera_pos.x -= oldMouse.x - event.mouseMove.x;
					context.camera_pos.y -= oldMouse.y - event.mouseMove.y;
					oldMouse.x = event.mouseMove.x;
					oldMouse.y = event.mouseMove.y;
				} else
				{
					oldMouse.x = event.mouseMove.x;
					oldMouse.y = event.mouseMove.y;
				}
				break;
			default:
				break;
			}
			if (movement.x > 0.1f) movement.x = 0.1f;
			if (movement.x < -0.1f) movement.x = -0.1f;
			if (movement.y > 0.1f) movement.y = 0.1f;
			if (movement.y < -0.1f) movement.y = -0.1f;
			break;
		}
	}
	context.camera_pos.x += movement.x;
	context.camera_pos.y += movement.y;
	if (!window->isOpen()) shouldClose = true;
}

void Game::loop()
{
}

void Game::draw()
{
	renderer->renderMap(*window, context);
}

void Game::cleanup()
{
	delete window;
	delete map;
	delete renderer;
	window = nullptr;
	map = nullptr;
	renderer = nullptr;
}

void Game::run()
{
	init();
	mapLoader->loadMap(*map, "test1");
	renderer->generateMap();
	while (!shouldClose)
	{
		poll();
		loop();
		draw();
	}
	cleanup();
}
