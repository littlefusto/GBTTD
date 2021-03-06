//
// Created by noop on 09.05.2022.
//

#include <JSONMapLoader.h>
#include <GameInput.h>


void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow &window, float zoom) {
	const sf::Vector2f beforeCoord{window.mapPixelToCoords(pixel)};
	sf::View view{window.getView()};
	view.zoom(zoom);
	window.setView(view);
	const sf::Vector2f afterCoord{window.mapPixelToCoords(pixel)};
	const sf::Vector2f offsetCoords{beforeCoord - afterCoord};
	view.move(offsetCoords);
	window.setView(view);
}

void GameInput::init() {
	moveRight = 0, moveLeft = 0, moveUp = 0, moveDown = 0;
	movement = {0, 0};
	oldMouse = {0, 0};
}

void GameInput::handleInput(Game *game) {
	while (game->getWindow()->pollEvent(event)) {
		switch (game->getGameState()) {
			case state_menu: {
				switch (event.type) {
					case sf::Event::KeyPressed: {
						switch(event.key.code){
							case sf::Keyboard::L: {
								std::string path = "map1";//TODO:move <--this<- somewhere else
								delete game->getMap();//TODO: create proper destructor!
								game->setMap(JSONMapLoader::loadMap(path));
								game->getRenderer()->generateMap();
								game->setGameState(state_map);
								break;
							}
							case sf::Keyboard::S: {
								std::string path = "map1";//<--you know what to do
								JSONMapLoader::saveMap(game->getMap(), path);
								break;
							}
							case sf::Keyboard::Escape: {
								game->setGameState(state_map);
								break;
							}
						default:
							break;
						}
						break;
					}
					case sf::Event::Closed: {
						game->getWindow()->close();
						break;
					}
					default: {
						break;
					}
				}
				break;
			}
			case state_map: {
				switch (event.type) {
					case sf::Event::Closed: {
						game->getWindow()->close();
						break;
					}
					case sf::Event::KeyPressed: {
						switch (event.key.code) {
							case sf::Keyboard::Right:
								moveRight = 0.1f;
								break;
							case sf::Keyboard::Left:
								moveLeft = 0.1f;
								break;
							case sf::Keyboard::Down:
								moveDown = 0.1f;
								break;
							case sf::Keyboard::Up:
								moveUp = 0.1f;
								break;
							case sf::Keyboard::B:
								game->setGameState(state_build);
								break;
							case sf::Keyboard::Escape:
								game->setGameState(state_menu);
								break;
							default: {
								break;
							}
						}
						break;
					}
					case sf::Event::KeyReleased: {
						switch (event.key.code) {
							case sf::Keyboard::Right:
								moveRight = 0.0f;
								break;
							case sf::Keyboard::Left:
								moveLeft = 0.0f;
								break;
							case sf::Keyboard::Down:
								moveDown = 0.0f;
								break;
							case sf::Keyboard::Up:
								moveUp = 0.0f;
								break;
							default: {
								break;
							}
						}
						break;
					}
					case Event::MouseButtonPressed: {
						switch (event.mouseButton.button) {
							case sf::Mouse::Left: {
								sf::Vector2i pos;
								pos.x = event.mouseButton.x;
								pos.y = event.mouseButton.y;
								sf::Vector2f pos_world = game->getWindow()->mapPixelToCoords(pos);
								pos.x = pos_world.x;
								pos.y = pos_world.y;
								game->getRenderer()->getClickedTiles(pos);
								break;
							}
							case sf::Mouse::Middle: {
								GameInput::MMBPressed = true;
								break;
							}
							case sf::Mouse::Right: {
								break;
							}
							default: {
								break;
							}
						}
						break;
					}
					case Event::MouseButtonReleased: {
						switch (event.mouseButton.button) {
							case sf::Mouse::Middle: {
								GameInput::MMBPressed = false;
								break;
							}
						}
						break;
					}
					case Event::MouseMoved: {
						if (GameInput::MMBPressed) {
							float zoom_x_mult =
									(float) game->getView()->getSize().x / game->getWindow()->getSize().x;
							float zoom_y_mult =
									(float) game->getView()->getSize().y / game->getWindow()->getSize().y;
							game->getView()->move(zoom_x_mult * (oldMouse.x - event.mouseMove.x),
												  zoom_y_mult * (oldMouse.y - event.mouseMove.y));
							oldMouse.x = event.mouseMove.x;
							oldMouse.y = event.mouseMove.y;
						} else {
							oldMouse.x = event.mouseMove.x;
							oldMouse.y = event.mouseMove.y;
						}
						break;
					}
					case sf::Event::MouseWheelScrolled: {
						sf::Vector2i pos;
						pos.x = event.mouseWheelScroll.x;
						pos.y = event.mouseWheelScroll.y;
						if (event.mouseWheelScroll.delta > 0.0f) {
							zoomViewAt(pos, *game->getWindow(), 0.9f);
						} else {
							zoomViewAt(pos, *game->getWindow(), 1.1f);
						}
						View *veew = (View *) ((void *) (game->getView()));
						*veew = game->getWindow()->getView();
						break;
					}
					default: {
						break;
					}
				}
				break;
			}
			case state_build: {
				switch (event.type) {
					case sf::Event::Closed: {
						game->getWindow()->close();
						break;
					}
					case sf::Event::KeyPressed: {
						switch (event.key.code) {
							case sf::Keyboard::D:
								moveRight = 0.1f;
								break;
							case sf::Keyboard::A:
								moveLeft = 0.1f;
								break;
							case sf::Keyboard::S:
								moveDown = 0.1f;
								break;
							case sf::Keyboard::W:
								moveUp = 0.1f;
								break;
							case sf::Keyboard::B:
								game->setGameState(state_build);
								break;
							case sf::Keyboard::Escape:
								game->setGameState(state_menu);
								break;
							default: {
								break;
							}
						}
						break;
					}
					case sf::Event::KeyReleased: {
						switch (event.key.code) {
							case sf::Keyboard::D:
								moveRight = 0;
								break;
							case sf::Keyboard::A:
								moveLeft = 0;
								break;
							case sf::Keyboard::S:
								moveDown = 0;
								break;
							case sf::Keyboard::W:
								moveUp = 0;
								break;
							default:{
								break;
							}
						}
						break;
					}
					case Event::MouseButtonPressed: {
						switch(event.mouseButton.button){
							case sf::Mouse::Left: {
								break;
							}
							case sf::Mouse::Middle: {
								GameInput::MMBPressed = true;
								break;
							}
							case sf::Mouse::Right: {
								break;
							}
							default: {
								break;
							}
						}
						break;
					}
					case Event::MouseButtonReleased: {
						switch(event.mouseButton.button){
							case sf::Mouse::Left: {
								sf::Vector2i pos;
								pos.x = event.mouseButton.x;
								pos.y = event.mouseButton.y;
								sf::Vector2f pos_world = game->getWindow()->mapPixelToCoords(pos);
								pos.x = pos_world.x;
								pos.y = pos_world.y;
								vector<Tile *> clicked_tiles = game->getRenderer()->getClickedTiles(pos);
								int possible_tiles = 0;
								if (clicked_tiles[0])
									possible_tiles += clicked_tiles[0]->registerSlopeChange(true,S);
								if (clicked_tiles[1])
									possible_tiles += clicked_tiles[1]->registerSlopeChange(true,W);
								if (clicked_tiles[2])
									possible_tiles += clicked_tiles[2]->registerSlopeChange(true,N);
								if (clicked_tiles[3])
									possible_tiles += clicked_tiles[3]->registerSlopeChange(true,E);
								if (possible_tiles == 4) {
									if (clicked_tiles[0]) clicked_tiles[0]->commitSlopeChange();
									if (clicked_tiles[1]) clicked_tiles[1]->commitSlopeChange();
									if (clicked_tiles[2]) clicked_tiles[2]->commitSlopeChange();
									if (clicked_tiles[3]) clicked_tiles[3]->commitSlopeChange();
								}
								game->getRenderer()->generateMap();
								break;
							}
							case sf::Mouse::Middle: {
								GameInput::MMBPressed = false;
								break;
							}
							case sf::Mouse::Right: {
								sf::Vector2i pos;
								pos.x = event.mouseButton.x;
								pos.y = event.mouseButton.y;
								sf::Vector2f pos_world = game->getWindow()->mapPixelToCoords(pos);
								pos.x = pos_world.x;
								pos.y = pos_world.y;
								vector<Tile *> clicked_tiles = game->getRenderer()->getClickedTiles(pos);
								int possible_tiles = 0;
								if (clicked_tiles[0])
									possible_tiles += clicked_tiles[0]->registerSlopeChange(false,S);
								if (clicked_tiles[1])
									possible_tiles += clicked_tiles[1]->registerSlopeChange(false,W);
								if (clicked_tiles[2])
									possible_tiles += clicked_tiles[2]->registerSlopeChange(false,N);
								if (clicked_tiles[3])
									possible_tiles += clicked_tiles[3]->registerSlopeChange(false,E);
								if (possible_tiles == 4) {
									if (clicked_tiles[0]) clicked_tiles[0]->commitSlopeChange();
									if (clicked_tiles[1]) clicked_tiles[1]->commitSlopeChange();
									if (clicked_tiles[2]) clicked_tiles[2]->commitSlopeChange();
									if (clicked_tiles[3]) clicked_tiles[3]->commitSlopeChange();
								}
								game->getRenderer()->generateMap();
								break;
							}
							default: {
								break;
							}
						}
						break;
					}
					case Event::MouseMoved: {
						if (GameInput::MMBPressed) {
							float zoom_x_mult =
									(float) game->getView()->getSize().x / game->getWindow()->getSize().x;
							float zoom_y_mult =
									(float) game->getView()->getSize().y / game->getWindow()->getSize().y;
							game->getView()->move(zoom_x_mult * (oldMouse.x - event.mouseMove.x),
												  zoom_y_mult * (oldMouse.y - event.mouseMove.y));
							oldMouse.x = event.mouseMove.x;
							oldMouse.y = event.mouseMove.y;
						} else {
							oldMouse.x = event.mouseMove.x;
							oldMouse.y = event.mouseMove.y;
						}
						break;
					}
					case sf::Event::MouseWheelScrolled: {
						sf::Vector2i pos;
						pos.x = event.mouseWheelScroll.x;
						pos.y = event.mouseWheelScroll.y;
						if (event.mouseWheelScroll.delta > 0.0f) {
							zoomViewAt(pos, *game->getWindow(), 0.9f);
						} else {
							zoomViewAt(pos, *game->getWindow(), 1.1f);
						}
						View *veew = (View *) ((void *) (game->getView()));
						*veew = game->getWindow()->getView();
						break;
					}
					default: {
						break;
					}
				}
				break;
			}
		}
		if (game->getGameState() == state_map | game->getGameState() == state_build) {
			movement.x = (moveRight - moveLeft);
			movement.y = (moveDown - moveUp);
		}
	}
	game->getView()->move(movement);
}