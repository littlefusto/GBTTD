//
// Created by cpukiller on 07.05.22.
//

#pragma once

#include <gbttd.h>
#include <Tile.h>

struct textureInfo {
	Image* image;
	Texture* texture;
	Vector2i maxNorthPixel;
	Vector2i maxEastPixel;
	Vector2i maxSouthPixel;
	Vector2i maxWestPixel;
};

class TextureHandler
{
private:
	std::map<std::string, sf::Image*> images;
	std::map<std::string, sf::Texture*> textures;
	std::pair<sf::Image, sf::Texture> atlas;
	static TextureHandler* singleton_;

	TextureHandler();

	~TextureHandler();

	void deleteImages();

	void deleteTextures();

	textureInfo textures_map[2][32]; // 2 for tile types and 32 for tile orientations and slopes
public:
	TextureHandler(TextureHandler &other) = delete;

	void operator=(const TextureHandler &) = delete;

	static TextureHandler* getInstance();

	static std::string tileSlopePathName(Slope slope);

	static std::string tileTypePathName(TileType tile_type, Slope slope);

	textureInfo& getTextureByTileType(Tile* tile);

	sf::Image* getImage(std::string &key);

	sf::Image* getImage(const char* key);

	sf::Texture* getTexture(std::string &key);

	sf::Texture* getTexture(const char* key);

	sf::Texture* getTextureAtlas();
};


//GBTTD_TEXTUREHANDLER_H
