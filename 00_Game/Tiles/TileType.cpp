//
// Created by cpukiller on 06.05.22.
//

#include "TileType.h"

TileType::TileType(std::string image_path,TileNames tile_name) : tile_name(tile_name){
    if (!tile_image.loadFromFile(image_path)) {
        throw std::invalid_argument("Image at" + image_path + " not found");
    }
}
