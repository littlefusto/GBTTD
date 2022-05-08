//
// Created by fusto on 08.05.22.
//

#include <gbttd.h>

MapLoader* MapLoader::singleton_ = nullptr;

std::string MapLoader::saveTile(Tile* tile){
	std::string tileBlock = "";
	return tileBlock;
}

MapLoader::MapLoader(){
}

void MapLoader::saveMap( std::string name){
	std::string data = "";

}

MapLoader* MapLoader::getInstance()
{
	if(singleton_==nullptr){
		singleton_ = new MapLoader();
	}
	return singleton_;
}