//
// Created by cpukiller on 07.05.22.
//

#pragma once

#include <gbttd.h>

class TextureHandler
{
private:
	std::map<std::string,sf::Image*> data;
	static TextureHandler* singleton_;
	TextureHandler();
	~TextureHandler();
	void deleteImages();
public:
	TextureHandler(TextureHandler &other) = delete;
	void operator=(const TextureHandler &) = delete;
	static TextureHandler *getInstance();
	sf::Image* getImage(std::string& key);
	sf::Image* getImage(const char* key);
};


//GBTTD_TEXTUREHANDLER_H
