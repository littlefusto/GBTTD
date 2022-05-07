//
// Created by cpukiller on 07.05.22.
//

#ifndef GBTTD_TEXTUREHANDLER_H
#define GBTTD_TEXTUREHANDLER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureHandler
{
private:
	std::map<std::string,sf::Image> data;
	TextureHandler singleton;
public:
	TextureHandler();
	sf::Image* getImage(std::string& key);
};


#endif //GBTTD_TEXTUREHANDLER_H
