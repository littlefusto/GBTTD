//
// Created by cpukiller on 09.05.22.
//

#include "JSONMapLoader.h"

void JSONMapLoader::saveMap(Map &map, std::string& path)
{
	vector<vector<Tile*>> &content = map.getContent();
	int mapXsize = map.getSize().x;
	int mapYsize = map.getSize().y;
	Json::Value savefile;
	savefile["Header"]["Size"][0] = mapXsize;
	savefile["Header"]["Size"][1] = mapYsize;

	for (int w = 0; w < mapXsize; w++)
	{
		for (int h = 0; h < mapYsize; h++)
		{
			savefile["Tiles"][w][h]["Type"] = content[h][w]->getTileType();
			savefile["Tiles"][w][h]["Slope"] = content[h][w]->getTileSlope();
			savefile["Tiles"][w][h]["Height"] = content[h][w]->getHeight();
		}
	}
	printf("%s\n",savefile.toStyledString().c_str());
	std::ofstream outfile(saves::saves + path);
	outfile << savefile.toStyledString() << std::endl;
	outfile.close();
}

Map* JSONMapLoader::loadMap(std::string& path) {
	ifstream fileToRead(saves::saves + path);
	Json::Value savefile;
	fileToRead >> savefile;
	Map* map = new Map();
	int mapXsize = savefile["Header"]["Size"][0].asInt();
	int mapYsize = savefile["Header"]["Size"][1].asInt();
	for (int w = 0; w < mapXsize; w++)
	{
		for (int h = 0; h < mapYsize; h++)
		{
			TileType tile_type = (TileType) savefile["Tiles"][w][h]["Type"].asInt();
			Slope slope = (Slope) savefile["Tiles"][w][h]["Slope"].asInt();
			int height = savefile["Tiles"][w][h]["Height"].asInt();
			map->getContent()[h][w] = new Tile(height, tile_type, slope);
		}
	}
	return map;
}
