//
// Created by cpukiller on 09.05.22.
//

#include "JSONMapLoader.h"

std::string slopeToString(Slope slope) {
	std::string slope_string = "";
	if(slope == FLAT){
		slope_string += "flat";
	}else if(slope & STEEP){
		slope_string += "steep_";
	}
	if(slope & N){
		slope_string += "N";
	}
	if(slope & E){
		slope_string += "E";
	}
	if(slope & S){
		slope_string += "S";
	}
	if(slope & W){
		slope_string += "W";
	}
	return slope_string;
}

Slope stringToSlope(const std::string& slope_string) {
	unsigned char slope = FLAT;
	if(slope_string.find("steep") != std::string::npos) {
		slope |= STEEP;
		slope_string.substr(5,slope_string.length()-5);
	}
	if(slope_string.find('N') != std::string::npos) {
		slope |= N;
	}
	if(slope_string.find('E') != std::string::npos) {
		slope |= E;
	}
	if(slope_string.find('S') != std::string::npos) {
		slope |= S;
	}
	if(slope_string.find('W') != std::string::npos) {
		slope |= W;
	}
	return (Slope) slope;
}

std::string tileTypeToString(TileType tileType) {
	std::string tile_type_string = "";
	if(tileType == DEFAULT){
		tile_type_string += "default";
	}else if(tileType == GRASS){
		tile_type_string += "grass";
	}else{
		tile_type_string += "default";
	}
	return tile_type_string;
}

TileType stringToTileType(const std::string& tile_type_string) {
	TileType tileType = DEFAULT;
	if( tile_type_string == "default"){
		tileType = DEFAULT;
	}else if(tile_type_string == "grass"){
		tileType = GRASS;
	}
}

void JSONMapLoader::saveMap(Map* map, std::string& path)
{
	vector<vector<Tile*>> &content = map->getContent();
	int mapXsize = map->getSize().x;
	int mapYsize = map->getSize().y;
	Json::Value savefile;
	savefile["Header"]["Size"][0] = mapXsize;
	savefile["Header"]["Size"][1] = mapYsize;

	for (int w = 0; w < mapXsize; w++)
	{
		for (int h = 0; h < mapYsize; h++)
		{
			savefile["Tiles"][w][h]["Type"] = tileTypeToString(content[h][w]->getTileType());
			savefile["Tiles"][w][h]["Slope"] = slopeToString(content[h][w]->getTileSlope());
			savefile["Tiles"][w][h]["Height"] = content[h][w]->getHeight();
		}
	}
	//printf("%s\n",savefile.toStyledString().c_str());
	std::ofstream outfile(saves::saves + path + ".json");
	outfile << savefile.toStyledString() << std::endl;
	outfile.close();
}

Map* JSONMapLoader::loadMap(std::string& path) {
	ifstream fileToRead(saves::saves + path + ".json");
	Json::Value savefile;
	fileToRead >> savefile;
	int mapXsize = savefile["Header"]["Size"][0].asInt();
	int mapYsize = savefile["Header"]["Size"][1].asInt();
	Map* map = new Map(mapXsize, mapYsize);
	for (int w = 0; w < mapXsize; w++)
	{
		for (int h = 0; h < mapYsize; h++)
		{
			TileType tile_type = stringToTileType(savefile["Tiles"][w][h]["Type"].asString());
			Slope slope = stringToSlope(savefile["Tiles"][w][h]["Slope"].asString());
			int height = savefile["Tiles"][w][h]["Height"].asInt();
			map->getContent()[h][w] = new Tile(height, tile_type, slope);
		}
	}
	return map;
}
