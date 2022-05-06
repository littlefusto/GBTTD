//
// Created by cpukiller on 06.05.22.
//

#ifndef GBTTD_TILETYPE_H
#define GBTTD_TILETYPE_H

#include <SFML/Graphics.hpp>

enum TileNames {
    DEFAULT=0,
    GREEN=1
};

class TileType {
private:
    sf::Image tile_image;
    TileNames tile_name;
public:
    TileType(std::string image_path,TileNames tile_name);
    sf::Image& getTileImage() {return tile_image;}
};


#endif //GBTTD_TILETYPE_H