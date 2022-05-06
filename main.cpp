#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "02_Domain/Domain.h"
//###//
using namespace std;
using namespace sf;
using namespace textures;
//###//

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "GBTTD");
    sf::Texture texture;
    if (!texture.loadFromFile(textures::tiles + "tile.png")) {
        return -1;
    }
    sf::Sprite sprite;
    sf::Sprite sprite1;
    sprite.setTexture(texture);
    sprite.setPosition(10.f,50.f);

    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}
