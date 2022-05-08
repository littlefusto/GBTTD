//
// Created by cpukiller on 07.05.22.
//

#pragma once

#include <gbttd.h>
#include <Tile.h>

class TextureHandler
{
private:
	std::map<std::string, sf::Image*> data;
	static TextureHandler* singleton_;

	TextureHandler();

	~TextureHandler();

	void deleteImages();

	sf::Image* textures_map[2][0b11111];
public:
	TextureHandler(TextureHandler &other) = delete;

	void operator=(const TextureHandler &) = delete;

	static TextureHandler* getInstance();

	static std::string tileSlopePathName(Slope slope);

	static std::string tileTypePathName(TileType tile_type, Slope slope);

	sf::Image* getTextureByTileType(Tile* tile);

	sf::Image* getImage(std::string &key);

	sf::Image* getImage(const char* key);
};


//GBTTD_TEXTUREHANDLER_H
