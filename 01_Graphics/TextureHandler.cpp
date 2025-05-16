//
// Created by cpukiller on 07.05.22.
//

#include <gbttd.h>

TextureHandler* TextureHandler::singleton_ = 0;

const std::string tiles[] = {
		"grass_flat.png",
		"grass_sloped_N.png",
		"grass_sloped_NE.png",
		"grass_sloped_NES.png",
		"grass_sloped_NEW.png",
		"grass_sloped_NS.png",
		"grass_sloped_NSW.png",
		"grass_sloped_NW.png",
		"grass_sloped_E.png",
		"grass_sloped_ES.png",
		"grass_sloped_ESW.png",
		"grass_sloped_EW.png",
		"grass_sloped_S.png",
		"grass_sloped_SW.png",
		"grass_sloped_W.png",

		"grass_steep_N.png",
		"grass_steep_E.png",
		"grass_steep_S.png",
		"grass_steep_W.png",

		"selected_tile.png",
		"tile.png"
};

TextureHandler::TextureHandler()
{
	for (const std::string &tile_path: tiles) {
		sf::Image* tile_image = new sf::Image;
		if (!tile_image->loadFromFile("../01_Graphics/tiles/" + tile_path))	{
			std::cerr << "Image at " + tile_path + " not found" << std::endl;
		} else {
			images.insert(std::pair(tile_path, tile_image));
			sf::Texture* tile_texture = new sf::Texture;
			tile_texture->loadFromImage(*tile_image);
			textures.insert(std::pair(tile_path, tile_texture));
		}
	}
	atlas.first.create((STEEP_N + 1) * TILE_WIDTH, (GRASS + 1) * TILE_HEIGHT * 2, sf::Color(0x00000000));
	for (unsigned char i = DEFAULT; i <= GRASS; i++) {
		for (unsigned char j = FLAT; j <= STEEP_N; j++)	{
			try	{
				std::string tile_name = tileTypePathName((TileType) i, (Slope) j);
				sf::Image* tile_image = getImage(tile_name);
				atlas.first.copy(*tile_image, j * TILE_WIDTH, i * TILE_HEIGHT * 2, sf::IntRect(0,0,0,0), true);
				sf::Texture* tile_texture = getTexture(tile_name);
				Vector2i maxNorthPixel = Vector2i(0,INT32_MAX);
				Vector2i maxEastPixel = Vector2i(0,0);
				Vector2i maxSouthPixel = Vector2i(0,0);
				Vector2i maxWestPixel = Vector2i(INT32_MAX,0);
				for(int x=0; x< tile_texture->getSize().x; x++) {
					for(int y=0; y< tile_texture->getSize().y; y++) {
						if(tile_image->getPixel(x,y).a > 0) {
							if(maxNorthPixel.y > y) maxNorthPixel = Vector2i(x,y);
							if(maxSouthPixel.y < y) maxSouthPixel = Vector2i(x,y);
							if(maxEastPixel.x < x) maxEastPixel = Vector2i(x,y);
							if(maxWestPixel.x > x) maxWestPixel = Vector2i(x,y);
						}
					}
				}
				textures_map[i][j] = textureInfo{
						.image = tile_image,
						.texture = tile_texture,
						.maxNorthPixel = maxNorthPixel,
						.maxEastPixel = maxEastPixel,
						.maxSouthPixel = maxSouthPixel,
						.maxWestPixel = maxWestPixel
				};

			} catch (const std::invalid_argument &e) {
				textures_map[i][j] = textureInfo{
						.image = nullptr,
						.texture = nullptr,
						.maxNorthPixel = Vector2i(-1,-1),
						.maxEastPixel = Vector2i(-1,-1),
						.maxSouthPixel = Vector2i(-1,-1),
						.maxWestPixel = Vector2i(-1,-1)
				};;
			}
		}
	}
	atlas.second = sf::Texture();
	atlas.second.loadFromImage(atlas.first);
}

TextureHandler::~TextureHandler()
{
	deleteImages();
	deleteTextures();
}

void TextureHandler::deleteImages()
{
	for (std::pair<const std::string, sf::Image*> image: images)
	{
		delete image.second;
	}
	images.clear();
}

void TextureHandler::deleteTextures()
{
	for (std::pair<const std::string, sf::Texture*> texture: textures)
	{
		delete texture.second;
	}
	images.clear();
}

TextureHandler* TextureHandler::getInstance()
{
	if (singleton_ == nullptr)
	{
		singleton_ = new TextureHandler();
	}
	return singleton_;
}

sf::Image* TextureHandler::getImage(const char* key)
{
	auto it = images.find(key);
	if (it == images.end())
	{
		return NULL;
	} else
	{
		return it->second;
	}
}

sf::Image* TextureHandler::getImage(std::string &key)
{
	return getImage(key.c_str());
}

sf::Texture* TextureHandler::getTexture(const char* key)
{
	auto it = textures.find(key);
	if (it == textures.end())
	{
		return NULL;
	} else
	{
		return it->second;
	}
}

sf::Texture* TextureHandler::getTexture(std::string &key)
{
	return getTexture(key.c_str());
}

textureInfo& TextureHandler::getTextureByTileType(Tile* tile)
{
	return textures_map[tile->getTileType()][tile->getTileSlope()];
}

std::string TextureHandler::tileTypePathName(TileType tile_type, Slope slope)
{
	std::string path;
	if (tile_type == DEFAULT)
	{
		return "tile.png";
	} else if (tile_type == GRASS)
	{
		path += "grass";
	}
	return (path + "_" + tileSlopePathName(slope) + ".png");
}

std::string TextureHandler::tileSlopePathName(Slope slope)
{
	std::string path;
	if (!slope)return "flat";
	if (slope & STEEP)
	{
		path += "steep_";
		switch (slope & NESW)
		{
		case N:
			return path += "N";
		case E:
			return path += "E";
		case S:
			return path += "S";
		case W:
			return path += "W";
		default:
			throw std::invalid_argument("invalid arguments: tile is improperly constructed");
		}
	} else
	{
		path += "sloped_";
		if (slope & N)path += "N";
		if (slope & E)path += "E";
		if (slope & S)path += "S";
		if (slope & W)
		{
			if ((slope & NES) == NES)//if sloped in all directions tile is invalid
			{
				throw std::invalid_argument(
						"improperly constructed tile: cannot have a tile with NESW flags set");
			} else { path += "W"; }
		}
	}

	return path;
}

Texture* TextureHandler::getTextureAtlas() {
	return &atlas.second;
}
