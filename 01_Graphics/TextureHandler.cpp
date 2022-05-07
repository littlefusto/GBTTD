//
// Created by cpukiller on 07.05.22.
//

#include <gbttd.h>

TextureHandler* TextureHandler::singleton_ = 0;

const std::string tiles[] = {
		"grass_flat.png",
		"grass_sloped_N.png",
		"grass_steep_E.png",
		"grass_sloped_E.png",
		"grass_sloped_NS.png",
		"grass_steep_N.png",
		"grass_sloped_ES.png",
		"grass_sloped_NSW.png",
		"grass_steep_S.png",
		"grass_sloped_ESW.png",
		"grass_sloped_NW.png",
		"grass_steep_W.png",
		"grass_sloped_NE.png",
		"grass_sloped_S.png",
		"selected_tile.png",
		"grass_sloped_NES.png",
		"grass_sloped_SW.png",
		"tile.png",
		"grass_sloped_NEW.png",
		"grass_sloped_W.png"
};

TextureHandler::TextureHandler()
{
	for (const std::string& tile_path : tiles) {
		sf::Image* tile_image = new sf::Image;
		if (!tile_image->loadFromFile("../01_Graphics/tiles/" + tile_path))
		{
			std::cerr << "Image at" + tile_path + " not found" << std::endl;
		} else {
			data.insert(std::pair(tile_path, tile_image));
		}
	}
}

TextureHandler::~TextureHandler() {
	deleteImages();
}

void TextureHandler::deleteImages() {
	for (std::pair<const std::string,sf::Image*> image : data) {
		delete image.second;
	}
	data.clear();
}

TextureHandler* TextureHandler::getInstance()
{
	if(singleton_==nullptr){
		singleton_ = new TextureHandler();
	}
	return singleton_;
}

sf::Image* TextureHandler::getImage(const char* key) {
	auto it = data.find(key);
	if(it == data.end()) {
		return NULL;
	} else {
		return it->second;
	}
}

sf::Image* TextureHandler::getImage(std::string& key)
{
	return getImage(key.c_str());
}