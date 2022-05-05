#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
//###//
using namespace std;
using namespace sf;
//###//

void thread_function()
{
	std::cout << std::this_thread::get_id() << "Goodbye, cruel world!" << std::endl;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	std::thread thread(&thread_function);
	thread.join();
	return 0;
}
