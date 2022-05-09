//
// Created by cpukiller on 09.05.22.
//

#include "JSONMapLoader.h"

static void JSONMapLoader::saveMap(Map &map)
{
	vector<vector<Tile*>> &content = map.getContent();
	int mapXsize = map.getSize().x;
	int mapYsize = map.getSize().y;
	Json::Value savefile;
	savefile["Header"]["Size"][0] = mapXsize;
	savefile["Header"]["Size"][0] = mapYsize;

	for (int w = 0; w < mapXsize; w++)
	{
		for (int h = 0; h < mapYsize; h++)
		{
			savefile["Tiles"][w][h]["Type"] = content[h][w]->getTileType();
			savefile["Tiles"][w][h]["Slope"] = content[h][w]->getTileSlope();
			savefile["Tiles"][w][h]["Height"] = content[h][w]->getHeight();
		}
	}
	printf("%s",savefile.asCString());
}
