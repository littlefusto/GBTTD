//
// Created by noop on 08.05.2022.
//
#include <gbttd.h>
#include "Game.h"

Game::Game() {
	view = sf::View(sf::FloatRect(0.f, 0.f, WINDOW_SIZE_X, WINDOW_SIZE_Y));
}

void Game::init()
{
	window = new RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "GBTTD");
	map = new Map();
	renderer = new Renderer(*map);
	mapLoader = new MapLoader();
}

void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	sf::View view{ window.getView() };
	view.zoom(zoom);
	window.setView(view);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
	window.setView(view);
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
			{
				sf::Vector2i pos;
				pos.x = event.mouseWheelScroll.x;
				pos.y = event.mouseWheelScroll.y;
				if (event.mouseWheelScroll.delta > 0.0f)
				{
					zoomViewAt(pos, *window, 0.9f);
				} else
				{
					zoomViewAt(pos, *window, 1.1f);
				}
				view = window->getView();
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
					sf::Vector2f pos_world = window->mapPixelToCoords(pos);
					//convert to integers
					//maybe change renderer to float
					pos.x = pos_world.x;
					pos.y = pos_world.y;
					renderer->getClickedTile(pos);
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
					float zoom_x_mult = (float)view.getSize().x/window->getSize().x;
					float zoom_y_mult = (float)view.getSize().y/window->getSize().y;
					view.move(zoom_x_mult*(oldMouse.x - event.mouseMove.x),zoom_y_mult*(oldMouse.y - event.mouseMove.y));
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
	view.move(movement);
	window->setView(view);
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
	delete renderer;
	window = nullptr;
	map = nullptr;
	renderer = nullptr;
}

void Game::run()
{
	init();
	window->setView(view);
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
