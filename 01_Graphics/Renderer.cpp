//
// Created by cpukiller on 06.05.22.
//

#include <gbttd.h>

Renderer::Renderer(Map &map) : map(map)
{
	point_at = sf::Vector2i(0, 0);
	selected_tile = sf::Vector2i(-1, -1);
	selected_tile_image = TextureHandler::getInstance()->getImage("selected_tile.png");
}

bool Renderer::generateMap()
{
	vector<vector<Tile*>> &content = map.getContent();
	map_image.create(map.getSize().x * TILE_WIDTH, map.getSize().y * TILE_HEIGTH + MAX_MAP_HEIGHT * 16);
	for (int i = 0; i < map.getSize().x; i++)
	{
		for (int j = 0; j < map.getSize().y; j++)
		{
			//right and down for every i
			//left and down for every j
			//rest is adjusting
			int x = (TILE_WIDTH / 2 * i) - (TILE_WIDTH / 2 * j) + ((map.getSize().x * TILE_WIDTH) / 2) -
					(TILE_WIDTH / 2);
			int y = (TILE_HEIGTH / 2 * i) + (TILE_HEIGTH / 2 * j) + 8 * (MAX_MAP_HEIGHT - content[j][i]->getHeight());
			sf::Image* source = TextureHandler::getInstance()->getTextureByTileType(content[j][i]);
			if (source == nullptr)
			{
				std::cerr << "Tile at x:" << i << " y:" << j << " has invalid type or slope" << std::endl;
			} else
			{
				map_image.copy(*source, x, y,
							   sf::IntRect(0, 0, 0, 0), true);
			}
		}
	}
	if (selected_tile.x >= 0)
	{
		map_image.copy(*selected_tile_image, selected_tile.x + 3, selected_tile.y, sf::IntRect(0, 0, 0, 0),
					   true);
	}
	sf::Color color = sf::Color(255, 0, 0);
	map_image.setPixel(point_at.x, point_at.y, color);
	map_texture.loadFromImage(map_image);
	map_sprite.setTexture(map_texture);
	map_sprite.setPosition(0.f, 0.f);
	return true;
}

Vector2i Renderer::getClickedTile(sf::Vector2i pos)
{
	Vector2i clicked_tile = Vector2i(-1,-1);
	vector<vector<Tile*>> &content = map.getContent();
	for (int i = 0; i < map.getSize().x; i++)
	{
		for (int j = 0; j < map.getSize().y; j++)
		{
			//right and down for every i
			//left and down for every j
			//rest is adjusting
			int x = (TILE_WIDTH / 2 * i) - (TILE_WIDTH / 2 * j) + ((map.getSize().x * TILE_WIDTH) / 2) -
					(TILE_WIDTH / 2);
			int y = (TILE_HEIGTH / 2 * i) + (TILE_HEIGTH / 2 * j) + 8 * (MAX_MAP_HEIGHT - content[j][i]->getHeight());
			sf::Image* source = TextureHandler::getInstance()->getTextureByTileType(content[j][i]);
			if (source == nullptr)
			{
				std::cerr << "Tile at x:" << i << " y:" << j << " has invalid type or slope" << std::endl;
			} else
			{
				int pixel_x = pos.x - x;
				int pixel_y = pos.y - y;
				if (pixel_x <= source->getSize().x && pixel_x >= 0 && pixel_y <= source->getSize().y && pixel_y >= 0 &&
					source->getPixel(pixel_x, pixel_y).a == 255)
				{
					//printf("COCK COCK %d %d a: %d\n",bla,blub,source->getPixel(bla,blub).a);
					//printf("COCK COCK x:%d y:%d a: \n",x,y);
					selected_tile = Vector2i(x, y);
					selected_tile_image->create(source->getSize().x, source->getSize().y);
					selected_tile_image->copy(*source, 0, 0);
					selected_tile_image->createMaskFromColor(Color(0, 255, 0), 200);
					clicked_tile = Vector2i(i,j);
				}
			}
		}
	}
	point_at = pos;
	generateMap();
	return clicked_tile;
}

void Renderer::renderMap(sf::RenderWindow &window)
{
	window.clear();
	window.draw(map_sprite);
	window.display();
}

/**
* Calculates the area of the parallelogram of the three points.
* This is actually the same as the area of the triangle defined by the three points, multiplied by 2.
* @return 2 * triangleArea(a,b,c)
*/
int perpDotProduct(sf::Vector2i a, sf::Vector2i b, sf::Vector2i c)
{
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}
/*
void Renderer::getClickedTile(sf::Vector2i pos)
{
	//Using the perp dot product to determine if the clicked point is above or below a line
	//Considered lines are along the edges of the tiles
	//TODO: Alternative: calculate the distance of the clicked point from one edge of the map
	//and divide it by the diagonal of one tile
	//First we consider lines running from left to right starting with the tile at the top
	int lastRun = 1;
	int this_run = 12;
	int y = -1;
	for (int i = 0; i <= map.getSize().x; i++)
	{
		sf::Vector2i v1 = { map.getSize().x / 2 * TILE_WIDTH - i * TILE_WIDTH / 2, i * TILE_HEIGTH / 2 };
		sf::Vector2i v2 = {
				map.getSize().x * TILE_WIDTH - i * TILE_WIDTH / 2, map.getSize().y / 2 * TILE_HEIGTH + i * TILE_HEIGTH / 2
		};
		int pdp = perpDotProduct(v1, v2, pos);
		this_run = (pdp > 0) ? 1 : -1;
		//printf("v1:%d %d v2: %d %d point: %d %d pdp=%d\n",v1.x,v1.y,v2.x,v2.y,point_at.x, point_at.y,pdp);
		if (lastRun == 1 && this_run == -1)
		{
			y = i - 1;
		}
		lastRun = this_run;
	}
	//Then we consider lines running from right to left starting with the tile at the top
	int x = -1;
	lastRun = 1;
	this_run = 12;
	for (int i = 0; i <= map.getSize().x; i++)
	{
		sf::Vector2i v1 = { map.getSize().x / 2 * TILE_WIDTH + i * TILE_WIDTH / 2, i * TILE_HEIGTH / 2 };
		sf::Vector2i v2 = { i * TILE_WIDTH / 2, map.getSize().y / 2 * TILE_HEIGTH + i * TILE_HEIGTH / 2 };
		int pdp = perpDotProduct(v1, v2, pos);
		this_run = (pdp < 0) ? 1 : -1;
		//printf("v1:%d %d v2: %d %d point: %d %d pdp=%d\n",v1.x,v1.y,v2.x,v2.y,point_at.x, point_at.y,pdp);
		if (lastRun == 1 && this_run == -1)
		{
			x = i - 1;
		}
		lastRun = this_run;
	}

	if (x >= 0 && y >= 0)
	{
		selected_tile.x = x;
		selected_tile.y = y;
		generateMap();
	}
}*/