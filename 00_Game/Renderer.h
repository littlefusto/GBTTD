//
// Created by tscharn on 06.05.22.
//

#ifndef GBTTD_RENDERER_H
#define GBTTD_RENDERER_H

#include <Map.h>
#include <SFML/Graphics.hpp>

class Renderer {
private:
    Map& map;
    sf::Texture map_texture;
    sf::Sprite map_sprite;
public:
    Renderer(Map& map);
    bool generateMap();
    void renderMap(sf::RenderWindow& window);
};


#endif //GBTTD_RENDERER_H
