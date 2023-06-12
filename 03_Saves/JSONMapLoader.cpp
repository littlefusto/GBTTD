//
// Created by cpukiller on 09.05.22.
//

#include "JSONMapLoader.h"
#include <json.hpp>

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
	return tileType;
}

std::vector<std::string> splitString(const std::string& s, const std::string& delimiter) {
	int pos = s.find(delimiter);
	std::vector<int> positions = std::vector<int>();
	positions.push_back(-1);
	while (pos > 0) {
		positions.push_back(pos);
		pos = s.find(delimiter, pos+1);
	}
	std::vector<std::string> tokens = std::vector<std::string>();
	for (int i = 0; i < positions.size() - 1; i++) {
		tokens.push_back(s.substr(positions[i] + 1, positions[i+1] - positions[i] - 1));
	}
	tokens.push_back(s.substr(positions[positions.size() - 1] + 1));
	return tokens;
}

std::string joinString(const std::vector<std::string>& tokens, const std::string& delimiter) {
	if (tokens.size() <= 0) return "";
	std::string s = tokens[0];
	for (int i = 1; i < tokens.size(); i++) {
		s += delimiter + tokens[i];
	}
	return s;
}

int find_last(const std::string& s, const std::string& t) {
    int lastPos = s.find(t);
    int newPos = 0;
    while ((newPos = s.find(t, lastPos + 1)) >= 0) {
        lastPos = newPos;
    }
    return lastPos;
}

void JSONMapLoader::saveMap(Map* map, std::string& saveName) {
	std::string savePath = saves::saves + saveName + ".json";
	std::string heightMapPath = saves::saves + saveName + ".png";

	printf("Create heightmap image...\n");
	// create image for the heightmap
	sf::Vector2i mapSize = map->getSize();
	sf::Image heightMapImg = sf::Image();
	heightMapImg.create(mapSize.x+1, mapSize.y+1);
	printf("Created heightmap.\n");
	const std::vector<std::vector<unsigned char>>& heightMap = map->getHeightMap();
	if (mapSize.x + 1 != heightMap[0].size() || mapSize.y + 1 != heightMap.size()) {
		std::cerr << "Map size desynced from heightmap size: (" << mapSize.x + 1 << ", " << mapSize.y + 1 << ") <> (" << heightMap[0].size() << ", " << heightMap.size() << ")" << std::endl;
	}
	for (int y = 0; y < heightMap.size(); y++) {
		for (int x = 0; x < heightMap[y].size(); x++) {
			heightMapImg.setPixel(x, y, sf::Color(heightMap[y][x], 0, 0));
		}
	}
	printf("Filled heightmap.\n");

	printf("Preparing JSON object...\n");
	json::JSON saveFile;
	
	saveFile["Header"]["Size"][0] = mapSize.x;
	saveFile["Header"]["Size"][1] = mapSize.y;
	saveFile["Header"]["MapName"] = saveName;
	saveFile["Header"]["Heightmap"] = heightMapPath;

	const std::vector<std::vector<Tile*>> &content = map->getContent();
	for (int h = 0; h < mapSize.y; h++)	{
		for (int w = 0; w < mapSize.x; w++) {
			saveFile["Tiles"][h][w]["Type"] = tileTypeToString(content[h][w]->getTileType());
		}
	}

	printf("Saving files...\n");
	// write data to files
	std::ofstream outfile(savePath);
	outfile << saveFile << std::endl;
	outfile.close();
	heightMapImg.saveToFile(heightMapPath);
	printf("Saving done.\nFiles:\t%s\n\t%s\n", savePath.c_str(), heightMapPath.c_str());
}

Map* JSONMapLoader::loadMap(std::string& saveName) {
	std::string savePath = saves::saves + saveName + ".json";
	printf("Read save file...\n");
	ifstream fileToRead(savePath);
	std::string full_file;
	std::string input;
	while(!getline(fileToRead, input).eof()) {
		full_file += input;
	}
	
	// load 
	json::JSON saveFile = json::JSON::Load(full_file);
	sf::Vector2i mapSize(saveFile["Header"]["Size"][0].ToInt(), saveFile["Header"]["Size"][1].ToInt());
	std::string heightMapPath = saveFile["Header"]["Heightmap"].ToString();
	Map* map = new Map(mapSize.x, mapSize.y);
	std::vector<std::vector<Tile*>> &tiles = map->getContent();
	//auto tiles = map->getContent();
	for (int h = 0; h < mapSize.y; h++) {
		for (int w = 0; w < mapSize.x; w++) {
			TileType tile_type = stringToTileType(saveFile["Tiles"][h][w]["Type"].ToString());
			delete tiles[h][w];
			tiles[h][w] = new Tile(tile_type);
		}
	}	
	
	printf("Load heightmap...\n");
	// load the heightmap from an image specified in the savefile
	auto &heightMap = map->getHeightMap();
	sf::Image heightMapImg;
	heightMapImg.loadFromFile(heightMapPath);
	sf::Vector2u heightMapSize = heightMapImg.getSize();
	if (heightMapSize.x != heightMap[0].size() || heightMapSize.y != heightMap.size()) {
		std::cerr << "Image size desynced from heightmap size: (" << heightMapSize.x + 1 << ", " << heightMapSize.y + 1 << ") <> (" << heightMap[0].size() << ", " << heightMap.size() << ")" << std::endl;
	}
	if (mapSize.x + 1 != heightMap[0].size() || mapSize.y + 1 != heightMap.size()) {
		std::cerr << "Map size desynced from heightmap size: (" << mapSize.x + 1 << ", " << mapSize.y + 1 << ") <> (" << heightMap[0].size() << ", " << heightMap.size() << ")" << std::endl;
	}
	for (int y = 0; y <= mapSize.y; y++) {
		for (int x = 0; x <= mapSize.x; x++) {
			heightMap[y][x] = heightMapImg.getPixel(x, y).r;
		}
	}

	map->updateSlopes();
	printf("Map loaded.\n");

	return map;
}
