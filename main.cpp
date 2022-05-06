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

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		renderer.generateMap();
		renderer.renderMap(window);
	}
	return 0;
}
