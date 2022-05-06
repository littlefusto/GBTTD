#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <Textures.h>
#include <Map.h>
#include "01_Graphics/Renderer.h"
//###//
using namespace std;
using namespace sf;
using namespace textures;
//###//

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "GBTTD");
	Map map = Map();
	Renderer renderer = Renderer(map);
	CameraContext context = CameraContext{ .zoom =  2.0f, .camera_pos =  Vector2f(15.0f, 15.0f) };
	Vector2f movement = { 0.0f, 0.0f };
	Vector2f oldMouse = { 0.0f, 0.0f };
	bool mouseButtonPressed = false;
	sf::Event event{};

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
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
			case Event::Resized:
			case Event::LostFocus:
			case Event::GainedFocus:
			case Event::TextEntered:
			case Event::MouseWheelMoved:
				break;
			case Event::MouseButtonPressed:
				mouseButtonPressed = true;
				break;
			case Event::MouseButtonReleased:
				mouseButtonPressed = false;
				break;
			case Event::MouseMoved:
				if (mouseButtonPressed)
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
			case Event::MouseEntered:
			case Event::MouseLeft:
			case Event::JoystickButtonPressed:
			case Event::JoystickButtonReleased:
			case Event::JoystickMoved:
			case Event::JoystickConnected:
			case Event::JoystickDisconnected:
			case Event::TouchBegan:
			case Event::TouchMoved:
			case Event::TouchEnded:
			case Event::SensorChanged:
			case Event::Count:
				break;
			}
			if (movement.x > 0.1f) movement.x = 0.1f;
			if (movement.x < -0.1f) movement.x = -0.1f;
			if (movement.y > 0.1f) movement.y = 0.1f;
			if (movement.y < -0.1f) movement.y = -0.1f;
		}
		context.camera_pos.x += movement.x;
		context.camera_pos.y += movement.y;
		renderer.renderMap(window, context);
	}
	return 0;
}
