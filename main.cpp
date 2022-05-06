#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <Textures.h>
#include <Map.h>
#include <Renderer.h>
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
    CameraContext context = CameraContext{zoom : 2.0f,camera_pos : Vector2f(15.0f,15.0f)};
    Vector2f movement = {0.0f,0.0f};
    Vector2f oldMouse = {0.0f,0.0f};
    bool mouseButtonPressed = false;
	sf::Event event{};

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
            if (event.type == sf::Event::MouseWheelScrolled) {
                if(event.mouseWheelScroll.delta > 0.0f) {
                    context.zoom *= 1.1;
                } else {
                    context.zoom /= 1.1;
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Left) {
                    movement.x += 0.1f;
                } else if(event.key.code == sf::Keyboard::Right) {
                    movement.x += -0.1f;
                } else if(event.key.code == sf::Keyboard::Up) {
                    movement.y += 0.1f;
                } else if(event.key.code == sf::Keyboard::Down) {
                    movement.y += -0.1f;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Left) {
                    movement.x += -0.1f;
                }
                else if(event.key.code == sf::Keyboard::Right) {
                    movement.x += 0.1f;
                }
                else if(event.key.code == sf::Keyboard::Up) {
                    movement.y += -0.1f;
                }
                else if(event.key.code == sf::Keyboard::Down) {
                    movement.y += 0.1f;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                mouseButtonPressed = true;
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                mouseButtonPressed = false;
            }
            if (event.type == sf::Event::MouseMoved) {
                if(mouseButtonPressed) {
                    context.camera_pos.x -= oldMouse.x - event.mouseMove.x;
                    context.camera_pos.y -= oldMouse.y - event.mouseMove.y;
                    oldMouse.x = event.mouseMove.x;
                    oldMouse.y = event.mouseMove.y;
                } else {
                    oldMouse.x = event.mouseMove.x;
                    oldMouse.y = event.mouseMove.y;
                }
            }
            if(movement.x > 0.1f) movement.x = 0.1f;
            if(movement.x < -0.1f) movement.x = -0.1f;
            if(movement.y > 0.1f) movement.y = 0.1f;
            if(movement.y < -0.1f) movement.y = -0.1f;
		}
        context.camera_pos.x += movement.x;
        context.camera_pos.y += movement.y;
        renderer.renderMap(window,context);

	}
	return 0;
}
