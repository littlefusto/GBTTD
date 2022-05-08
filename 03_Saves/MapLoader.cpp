//
// Created by fusto on 08.05.22.
//

#include <gbttd.h>

MapLoader* MapLoader::singleton_ = 0;

MapLoader::MapLoader(){

}

MapLoader* MapLoader::getInstance()
{
	if(singleton_==nullptr){
		singleton_ = new MapLoader();
	}
	return singleton_;
}