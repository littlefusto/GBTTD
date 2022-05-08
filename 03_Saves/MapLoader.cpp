//
// Created by fusto on 08.05.22.
//

#include <gbttd.h>


MapLoader* MapLoader::singleton_ = nullptr;

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

MapLoader::MapLoader(){
}

void MapLoader::saveMap(Map& map, std::string name){
	std::string data = "";
	data += saveTile(map.getContent()[0][0]);

	std::ofstream outfile("../03_Saves/saves/" + name + ".map");
	outfile << data << std::endl;
	outfile.close();
}

MapLoader* MapLoader::getInstance()
{
	if(singleton_==nullptr){
		singleton_ = new MapLoader();
	}
	return singleton_;
}