//
// Created by fusto on 08.05.22.
//

#include <gbttd.h>

using namespace saves;

MapLoader* MapLoader::singleton_ = nullptr;

MapLoader::MapLoader(){
}

std::string MapLoader::saveTile(Tile* tile){
	std::string tileBlock = "height = " + to_string(tile->getHeight());
	tileBlock += "\ntype = ";

	if(tile->getTileType() == DEFAULT){
		tileBlock += "default";
	}else if(tile->getTileType() == GRASS){
		tileBlock += "grass";
	}else{
		tileBlock += "default";
	}
	tileBlock += "\nslope = ";

	if(tile->getTileSlope() == FLAT){
		tileBlock += "flat";
	}else if(tile->getTileSlope() == STEEP){
		tileBlock += "steep_";
	}else{
		if(tile->getTileSlope() == N){
			tileBlock += "N";
		}
		if(tile->getTileSlope() == E){
			tileBlock += "E";
		}
		if(tile->getTileSlope() == S){
			tileBlock += "S";
		}
		if(tile->getTileSlope() == W){
			tileBlock += "W";
		}
	}
	tileBlock += "\n";

	return tileBlock;
}

void MapLoader::saveMap(Map& map, const std::string& name){
	mapXsize = map.getSize().x;
	mapYsize = map.getSize().y;
	std::string data = to_string(mapXsize) + "x" + to_string(mapYsize) + "\n";

	for(int w=0; w<mapXsize;w++){
		for(int h=0; h<mapYsize;h++){
			data += "tile" + to_string(w) + "_" + to_string(h) + "\n";
			data += saveTile(map.getContent()[w][h]);
		}
	}

	std::ofstream outfile(saves::saves + "saves/" + name + ".map");
	outfile << data << std::endl;
	outfile.close();
}

std::string MapLoader::getAttribute(const std::string& tileString, const std::string& attribute){
	std::string handlerString;
	handlerString = tileString.substr(tileString.find(attribute + " = ")+attribute.length() + 3);
	handlerString = handlerString.substr(0,handlerString.find('\n'));
	return handlerString;
}

Tile* MapLoader::loadTile(const std::string& tileString){
	std::string currAttribute;
	int height = stoi(getAttribute(tileString, "height"));

	TileType tileType = DEFAULT;
	currAttribute = getAttribute(tileString, "type");
	if( currAttribute == "default"){
		tileType = DEFAULT;
	}else if(currAttribute == "grass"){
		tileType = GRASS;
	}

	unsigned char slope = FLAT;
	currAttribute = getAttribute(tileString, "slope");

	if(currAttribute.find("steep") != std::string::npos) {
		slope |= STEEP;
		currAttribute.substr(5,currAttribute.length()-5);
	}
	if(currAttribute.find('N') != std::string::npos) {
		slope |= N;
	}
	if(currAttribute.find('E') != std::string::npos) {
		slope |= E;
	}
	if(currAttribute.find('S') != std::string::npos) {
		slope |= S;
	}
	if(currAttribute.find('W') != std::string::npos) {
		slope |= W;
	}
	return new Tile(height, tileType, static_cast<Slope>(slope));
}

void MapLoader::loadMap(Map& map, const std::string& name){
	std::string input;
	ifstream fileToRead(saves::saves + name + ".map");
	getline(fileToRead, input);
	mapXsize = input[0] - '0';
	mapYsize = input[2] - '0';
	map.getContent().resize(mapXsize);
	for(int i=0;i<mapXsize;i++){
		map.getContent()[i].resize(mapYsize);
	}
	getline(fileToRead, input);
	bool continue_loop = true;
	while(continue_loop) {
		int x = input[4]- '0';
		int y = input[6]- '0';
		string tile_stuff;
		do{
			if((getline(fileToRead, input)).eof()) {
				continue_loop=false;
				break;
			}
			tile_stuff += input + "\n";
		} while(input.find("tile") == std::string::npos);
		Tile* tile = loadTile(tile_stuff);
		map.getContent()[y][x] = tile;
	}
}

MapLoader* MapLoader::getInstance()
{
	if(singleton_==nullptr){
		singleton_ = new MapLoader();
	}
	return singleton_;
}