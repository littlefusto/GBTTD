//
// Created by cpukiller on 06.05.22.
//

#include <gbttd.h>

Renderer::Renderer(Map &map) : map(map)
{
	point_at = sf::Vector2i(0, 0);
	selected_tile = sf::Vector2i(-1, -1);
	selected_tile_image = TextureHandler::getInstance()->getImage("selected_tile.png");
	generateMap();
}

bool Renderer::generateMap()
{
	vector<vector<Tile*>> &content = map.getContent();
	map_image.create(MAP_SIZE * TILE_WIDTH, MAP_SIZE * TILE_HEIGTH);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			//right and down for every i
			//left and down for every j
			//rest is adjusting
			int x = (TILE_WIDTH / 2 * i) - (TILE_WIDTH / 2 * j) + ((MAP_SIZE * TILE_WIDTH) / 2) -
				(TILE_WIDTH / 2);
			int y = (TILE_HEIGTH / 2 * i) + (TILE_HEIGTH / 2 * j);
			sf::Image source;
			source.loadFromFile(textures::tiles + map.tileTypePathName(content[j][i]->getTileInfo()));
			map_image.copy(source, x, y + 8 * (MAX_MAP_HEIGHT - content[i][j]->getHeight()),
				       sf::IntRect(0, 0, 0, 0), true);
		}
	}
	if (selected_tile.x >= 0)
	{
		int i = selected_tile.x;
		int j = selected_tile.y;
		int x = (TILE_WIDTH / 2 * i) - (TILE_WIDTH / 2 * j) + (MAP_SIZE * TILE_WIDTH) / 2 - TILE_WIDTH / 2;
		int y = (TILE_HEIGTH / 2 * i) + (TILE_HEIGTH / 2 * j);
		map_image.copy(*selected_tile_image, x, y /*+ 8*/, sf::IntRect(0, 0, 0, 0),
			       true); //MAYBE CHANGE 8 TO SMTH ELSE!!!
	}                                                                //+ 8 offsets the hitbox to an odd place
	sf::Color color = sf::Color(255, 0, 0);
	map_image.setPixel(point_at.x, point_at.y, color);
	map_texture.loadFromImage(map_image);
	map_sprite.setTexture(map_texture);
	map_sprite.setPosition(0.f, 0.f);
	return true;
}

void Renderer::renderMap(sf::RenderWindow &window, CameraContext &context)
{
	window.clear();
	pos = context.camera_pos;
	pos.x -= MAP_SIZE * TILE_WIDTH * (context.zoom / 2 - 1);
	pos.y -= MAP_SIZE * TILE_HEIGTH * (context.zoom / 2 - 1);
	map_sprite.setPosition(pos);
	map_sprite.setScale(context.zoom, context.zoom);
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

Tile* Renderer::getClickedTile(sf::Vector2i pos, CameraContext &context)
{
	//Remove zoom and shift of the map
	sf::Vector2f map_pos = map_sprite.getPosition();
	pos.x -= map_pos.x;
	pos.y -= map_pos.y;
	point_at.x = pos.x / context.zoom;
	point_at.y = pos.y / context.zoom;

	//Using the perp dot product to determine if the clicked point is above or below a line
	//Considered lines are along the edges of the tiles
	//TODO: Alternative: calculate the distance of the clicked point from one edge of the map
	//and divide it by the diagonal of one tile
	//First we consider lines running from left to right starting with the tile at the top
	int lastRun = 1;
	int this_run = 12;
	int y = -1;
	for (int i = 0; i <= MAP_SIZE; i++)
	{
		sf::Vector2i v1 = { MAP_SIZE / 2 * TILE_WIDTH - i * TILE_WIDTH / 2, i * TILE_HEIGTH / 2 };
		sf::Vector2i v2 = {
			MAP_SIZE * TILE_WIDTH - i * TILE_WIDTH / 2, MAP_SIZE / 2 * TILE_HEIGTH + i * TILE_HEIGTH / 2
		};
		int pdp = perpDotProduct(v1, v2, point_at);
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
	for (int i = 0; i <= MAP_SIZE; i++)
	{
		sf::Vector2i v1 = { MAP_SIZE / 2 * TILE_WIDTH + i * TILE_WIDTH / 2, i * TILE_HEIGTH / 2 };
		sf::Vector2i v2 = { i * TILE_WIDTH / 2, MAP_SIZE / 2 * TILE_HEIGTH + i * TILE_HEIGTH / 2 };
		int pdp = perpDotProduct(v1, v2, point_at);
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
}