//
// Created by noop on 09.05.2022.
//
#pragma once

#include <gbttd.h>
#include "JSONMapLoader.h"
#include <Game.h>


void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow &window, float zoom)
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

void Game::handleInput()
{
	while (window->pollEvent(event))
	{
		switch (gameState)
		{
		case state_menu:
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::L)
				{
					std::string path = "map1";//TODO:move <--this<- somewhere else
					delete map;//TODO: create proper destructor!
					map = JSONMapLoader::loadMap(path);
					renderer->generateMap();
					gameState = state_map;
				}
				if (event.key.code == sf::Keyboard::S)
				{
					std::string path = "map1";//<--you know what to do
					JSONMapLoader::saveMap(map, path);
				}
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
				*view = window->getView();
			}
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Right:
					movement.x += 0.1f;
					break;
				case sf::Keyboard::Left:
					movement.x += -0.1f;
					break;
				case sf::Keyboard::Down:
					movement.y += 0.1f;
					break;
				case sf::Keyboard::Up:
					movement.y += -0.1f;
					break;
				case sf::Keyboard::B:
					gameState = state_build;
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
				case sf::Keyboard::Right:
					movement.x = 0.0f;
					break;
				case sf::Keyboard::Left:
					movement.x = 0.0f;
					break;
				case sf::Keyboard::Down:
					movement.y = 0.0f;
					break;
				case sf::Keyboard::Up:
					movement.y = 0.0f;
					break;
				default:
					break;
				}
				break;
			case Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					sf::Vector2i pos;
					pos.x = event.mouseButton.x;
					pos.y = event.mouseButton.y;
					sf::Vector2f pos_world = window->mapPixelToCoords(pos);
					//convert to integers
					//maybe change renderer to float
					pos.x = pos_world.x;
					pos.y = pos_world.y;
					renderer->getClickedTiles(pos);
				}
					break;
				case sf::Mouse::Right:
					RMBPressed = true;
					break;
				default:
					break;
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
					float zoom_x_mult = (float) view->getSize().x / window->getSize().x;
					float zoom_y_mult = (float) view->getSize().y / window->getSize().y;
					view->move(zoom_x_mult * (oldMouse.x - event.mouseMove.x),
						   zoom_y_mult * (oldMouse.y - event.mouseMove.y));
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
			break;
		case state_build:
			switch (event.type)
			{
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
				*view = window->getView();
			}
				break;
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::D:
					movement.x += 0.1f;
					break;
				case sf::Keyboard::A:
					movement.x += -0.1f;
					break;
				case sf::Keyboard::S:
					movement.y += 0.1f;
					break;
				case sf::Keyboard::W:
					movement.y += -0.1f;
					break;
				case sf::Keyboard::B:
					gameState = state_build;
					break;
				case sf::Keyboard::Escape:
					gameState = state_menu;
					break;
				default:
					break;
				}
				break;
			}
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::D:
					movement.x += -0.1f;
					break;
				case sf::Keyboard::A:
					movement.x += 0.1f;
					break;
				case sf::Keyboard::S:
					movement.y += -0.1f;
					break;
				case sf::Keyboard::W:
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
					mouseWasMoved = false;
				} else if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i pos;
					pos.x = event.mouseButton.x;
					pos.y = event.mouseButton.y;
					sf::Vector2f pos_world = window->mapPixelToCoords(pos);
					pos.x = pos_world.x;
					pos.y = pos_world.y;
					vector<Tile*> clicked_tiles = renderer->getClickedTiles(pos);
					/*if(map->getContent()[pos.y][pos.x] == nullptr && map->getContent()[pos.y][pos.x]->getHeight() < MAX_MAP_HEIGHT ){
						map->getContent()[pos.y][pos.x] = new Tile(
								map->getContent()[pos.y][pos.x]->getHeight()+1,
								map->getContent()[pos.y][pos.x]->getTileType(),
								map->getContent()[pos.y][pos.x]->getTileSlope()
						);
					}*/
					if(clicked_tiles[0]) clicked_tiles[0]->setHeight(clicked_tiles[0]->getHeight() + 1);
					if(clicked_tiles[1]) clicked_tiles[1]->setHeight(clicked_tiles[1]->getHeight() + 2);
					if(clicked_tiles[2]) clicked_tiles[2]->setHeight(clicked_tiles[2]->getHeight() + 3);
					if(clicked_tiles[3]) clicked_tiles[3]->setHeight(clicked_tiles[3]->getHeight() + 4);
					renderer->generateMap();
				}
				break;
			case Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					RMBPressed = false;
					if (!mouseWasMoved)
					{
						sf::Vector2i pos;
						pos.x = event.mouseButton.x;
						pos.y = event.mouseButton.y;
						sf::Vector2f pos_world = window->mapPixelToCoords(pos);
						pos.x = pos_world.x;
						pos.y = pos_world.y;
						/*pos = renderer->getClickedTile(pos);
						if(map->getContent()[pos.y][pos.x]->getHeight() < MAX_MAP_HEIGHT){
							map->getContent()[pos.y][pos.x] = new Tile(
									map->getContent()[pos.y][pos.x]->getHeight()-1,
									map->getContent()[pos.y][pos.x]->getTileType(),
									map->getContent()[pos.y][pos.x]->getTileSlope()
							);
						}*/
						vector<Tile*> clicked_tiles = renderer->getClickedTiles(pos);
						/*if(map->getContent()[pos.y][pos.x] == nullptr && map->getContent()[pos.y][pos.x]->getHeight() < MAX_MAP_HEIGHT ){
							map->getContent()[pos.y][pos.x] = new Tile(
									map->getContent()[pos.y][pos.x]->getHeight()+1,
									map->getContent()[pos.y][pos.x]->getTileType(),
									map->getContent()[pos.y][pos.x]->getTileSlope()
							);
						}*/
						if(clicked_tiles[0]) clicked_tiles[0]->setHeight(clicked_tiles[0]->getHeight() + 1);
						if(clicked_tiles[1]) clicked_tiles[1]->setHeight(clicked_tiles[1]->getHeight() + 2);
						if(clicked_tiles[2]) clicked_tiles[2]->setHeight(clicked_tiles[2]->getHeight() + 3);
						if(clicked_tiles[3]) clicked_tiles[3]->setHeight(clicked_tiles[3]->getHeight() + 4);
					}
				}
				break;
			case Event::MouseMoved:
				if (RMBPressed)
				{
					mouseWasMoved = true;
					float zoom_x_mult = (float) view->getSize().x / window->getSize().x;
					float zoom_y_mult = (float) view->getSize().y / window->getSize().y;
					view->move(zoom_x_mult * (oldMouse.x - event.mouseMove.x),
						   zoom_y_mult * (oldMouse.y - event.mouseMove.y));
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
			break;
		}
		if (gameState == state_map | gameState == state_build)
		{
			if (movement.x > 0.1f) movement.x = 0.1f;
			if (movement.x < -0.1f) movement.x = -0.1f;
			if (movement.y > 0.1f) movement.y = 0.1f;
			if (movement.y < -0.1f) movement.y = -0.1f;
		}
	}
}