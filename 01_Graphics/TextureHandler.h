//
// Created by cpukiller on 07.05.22.
//

#ifndef GBTTD_TEXTUREHANDLER_H
#define GBTTD_TEXTUREHANDLER_H

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


#endif //GBTTD_TEXTUREHANDLER_H
