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
	for (const std::string &tile_path: tiles)
	{
		sf::Image* tile_image = new sf::Image;
		if (!tile_image->loadFromFile("../01_Graphics/tiles/" + tile_path))
		{
			std::cerr << "Image at" + tile_path + " not found" << std::endl;
		} else
		{
			data.insert(std::pair(tile_path, tile_image));
		}
	}
	for (unsigned char i = DEFAULT; i <= GRASS; i++)
	{
		for (unsigned char j = FLAT; j <= STEEP_N; j++)
		{
			try
			{
				std::string tile_name = tileTypePathName((TileType) i, (Slope) j);
				textures_map[i][j] = getImage(tile_name);
			} catch (const std::invalid_argument &e)
			{
				textures_map[i][j] = nullptr;
			}
		}
	}
}

TextureHandler::~TextureHandler()
{
	deleteImages();
}

void TextureHandler::deleteImages()
{
	for (std::pair<const std::string, sf::Image*> image: data)
	{
		delete image.second;
	}
	data.clear();
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
	auto it = data.find(key);
	if (it == data.end())
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

sf::Image* TextureHandler::getTextureByTileType(Tile* tile)
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