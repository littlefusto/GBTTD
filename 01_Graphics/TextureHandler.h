//
// Created by cpukiller on 07.05.22.
//

#pragma once

#include <gbttd.h>
#include <Tile.h>

struct textureInfo {
	Image* texture;
	Vector2i maxNorthPixel;
	Vector2i maxEastPixel;
	Vector2i maxSouthPixel;
	Vector2i maxWestPixel;
};

class TextureHandler
{
private:
	std::map<std::string, sf::Image*> data;
	static TextureHandler* singleton_;

	TextureHandler();

	~TextureHandler();

	void deleteImages();

	textureInfo textures_map[2][0b11111];
public:
	TextureHandler(TextureHandler &other) = delete;

	void operator=(const TextureHandler &) = delete;

	static TextureHandler* getInstance();

	static std::string tileSlopePathName(Slope slope);

	static std::string tileTypePathName(TileType tile_type, Slope slope);

	textureInfo& getTextureByTileType(Tile* tile);

	sf::Image* getImage(std::string &key);

	sf::Image* getImage(const char* key);
};


//GBTTD_TEXTUREHANDLER_H
