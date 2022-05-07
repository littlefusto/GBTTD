#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <Textures.h>
#include <Map.h>
#include "01_Graphics/Renderer.h"
#include <Game.h>
//###//
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-designator"
using namespace std;
using namespace sf;
//###//

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "GBTTD");
	Map map = Map();
	Renderer renderer = Renderer(map);
	CameraContext context = CameraContext{ zoom : 2.0f, camera_pos : Vector2f(0.0f, 0.0f) };
	Vector2f movement = { 0.0f, 0.0f };
	Vector2f oldMouse = { 0.0f, 0.0f };
	bool RMBPressed = false;
	game_state gameState = state_map;
	sf::Event event{};

	while (window.isOpen())
	{
		while (window.pollEvent(event))
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
					window.close();
					break;
				default:
					break;
				}
				break;
			case state_map:
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
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
						renderer.getClickedTile(pos, context);
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
		renderer.renderMap(window, context);
	}
	return 0;
}

#pragma clang diagnostic pop