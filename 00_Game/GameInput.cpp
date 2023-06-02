//
// Created by noop on 09.05.2022.
//
#include <JSONMapLoader.h>
#include <gbttd.h>

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

/**
 * Handles a single event assuming the current GameState is STATE_MENU.
*/
void GameInput::handleMenuEvent(Game *game, sf::Event &event) {
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch(event.key.code)
		{
		case sf::Keyboard::L: {
			std::string path = "map1";//TODO:move <--this<- somewhere else
			delete game->getMap();//TODO: create proper destructor!
			game->setMap(JSONMapLoader::loadMap(path));
			game->getRenderer()->generateMap();
			game->setGameState(STATE_MAP);
			break;
		}
		case sf::Keyboard::S: {
			std::string path = "map1";//<--you know what to do
			JSONMapLoader::saveMap(game->getMap(), path);
			break;
		}
		default:
			break;
		}
		break;
	case sf::Event::Closed:
		game->getWindow()->close();
		break;
	default:
		break;
	}
}

/**
 * Handles a single event assuming the current GameState is STATE_BUILD.
*/
void GameInput::handleBuildEvent(Game *game, sf::Event &event) {
	switch (event.type)
	{
	case sf::Event::KeyPressed: {
		switch (event.key.code) {
			case sf::Keyboard::D:
			case sf::Keyboard::Right:
				moveRight = 0.1f;
				break;
			case sf::Keyboard::A:
			case sf::Keyboard::Left:
				moveLeft = 0.1f;
				break;
			case sf::Keyboard::S:
			case sf::Keyboard::Down:
				moveDown = 0.1f;
				break;
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
				moveUp = 0.1f;
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
			case sf::Keyboard::Right:
				moveRight = 0;
				break;
			case sf::Keyboard::A:
			case sf::Keyboard::Left:
				moveLeft = 0;
				break;
			case sf::Keyboard::S:
			case sf::Keyboard::Down:
				moveDown = 0;
				break;
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
				moveUp = 0;
				break;
			default:{
				break;
			}
		}
		break;
	}
	case Event::MouseButtonPressed: {
		switch(event.mouseButton.button) {
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
		sf::Vector2i pos(event.mouseButton.x, event.mouseButton.y);
		sf::Vector2f worldPos = game->getWindow()->mapPixelToCoords(pos);
		sf::Vector2i clickedVertex = game->getRenderer()->getClickedVertex(worldPos);
		switch(event.mouseButton.button) {
			case sf::Mouse::Left: {
				game->getMap()->raiseHeight(clickedVertex.x, clickedVertex.y);
				game->getRenderer()->updateRect(clickedVertex.x - MAX_MAP_HEIGHT, clickedVertex.y - MAX_MAP_HEIGHT, 2 * MAX_MAP_HEIGHT + 1, 2 * MAX_MAP_HEIGHT + 1);
				break;
			}
			case sf::Mouse::Middle: {
				GameInput::MMBPressed = false;
				break;
			}
			case sf::Mouse::Right: {
				game->getMap()->lowerHeight(clickedVertex.x, clickedVertex.y);
				game->getRenderer()->updateRect(clickedVertex.x - MAX_MAP_HEIGHT, clickedVertex.y - MAX_MAP_HEIGHT, 2 * MAX_MAP_HEIGHT + 1, 2 * MAX_MAP_HEIGHT + 1);
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
	default:
		break;
	
	}
}

/**
 * Handles a single event assuming the current GameState is STATE_MAP.
*/
void GameInput::handleMapEvent(Game *game, sf::Event &event) {
	switch (event.type)	{
	case sf::Event::KeyPressed: {
		switch (event.key.code) {
			case sf::Keyboard::Right:
			case sf::Keyboard::D:
				moveRight = 0.1f;
				break;
			case sf::Keyboard::Left:
			case sf::Keyboard::A:
				moveLeft = 0.1f;
				break;
			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				moveDown = 0.1f;
				break;
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				moveUp = 0.1f;
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
			case sf::Keyboard::D:
				moveRight = 0.0f;
				break;
			case sf::Keyboard::Left:
			case sf::Keyboard::A:
				moveLeft = 0.0f;
				break;
			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				moveDown = 0.0f;
				break;
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
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
	default:
		break;
	}
}

/**
 * Handles all events currently in the event queue and calls different functions dependent on the GameState.
 * Also handles the GameState itself.
*/
void GameInput::handleInput(Game *game) {
	while (game->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) { // handle closing the window
			game->getWindow()->close();
			break;
		} else if (event.type == sf::Event::Resized) { // handle resizing of the window
			View* view = game->getView();
			sf::Vector2u windowSize = game->getWindow()->getSize();
			sf::Vector2f viewSize = view->getSize();
			sf::Vector2f viewScale = sf::Vector2f(viewSize.x / oldWindowSize.x, viewSize.y / oldWindowSize.y);
			sf::Vector2f viewCenter = view->getCenter();
			view->setSize(windowSize.x * viewScale.x, windowSize.y * viewScale.y);
			view->setCenter(viewCenter);
			game->getWindow()->setView(*view);
			oldWindowSize = game->getWindow()->getSize();
		} else if (event.type == sf::Event::KeyReleased) { // Update game state if certain buttons are pressed
			switch (event.key.code)	{
			case sf::Keyboard::Escape: {
				// open/close menu
				if (game->getGameState() == STATE_MENU) {
					game->setGameState(STATE_MAP);
				} else {
					game->setGameState(STATE_MENU);
				}
				break;
			}
			case sf::Keyboard::B: {
				// open/close build mode
				if (game->getGameState() == STATE_BUILD) {
					game->setGameState(STATE_MAP);
				} else if (game->getGameState() != STATE_MENU) {
					game->setGameState(STATE_BUILD);
				}
				break;
			}
			default:
				break;
			}
		}
		// handle events differently depending on the current game state
		switch (game->getGameState()) {
			case STATE_MENU: {
				handleMenuEvent(game, event);
				break;
			}
			case STATE_MAP: {
				handleMapEvent(game, event);
				break;
			}
			case STATE_BUILD: {
				handleBuildEvent(game, event);
				break;
			}
		}
		movement.x = (moveRight - moveLeft);
		movement.y = (moveDown - moveUp);
	}
	if (game->getGameState() == STATE_MAP || game->getGameState() == STATE_BUILD) {
		game->getView()->move(movement);
	}
}