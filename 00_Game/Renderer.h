//
// Created by tscharn on 06.05.22.
//

#ifndef GBTTD_RENDERER_H
#define GBTTD_RENDERER_H

#include <Map.h>
#include <SFML/Graphics.hpp>
#include <TextureHandler.h>

struct CameraContext {
    float zoom;
    sf::Vector2f camera_pos;
};

class Renderer {
private:
    Map& map;
    TextureHandler textureHandler;
    sf::Texture map_texture;
    sf::Sprite map_sprite;
public:
    Renderer(Map& map);
    bool generateMap();
    void renderMap(sf::RenderWindow& window, CameraContext& context);
};


#endif //GBTTD_RENDERER_H
