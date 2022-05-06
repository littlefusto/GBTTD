//
// Created by tscharn on 06.05.22.
//

#include "Renderer.h"

Renderer::Renderer(Map& map) : map(map) {
    generateMap();
}

bool Renderer::generateMap() {
    vector<vector<Tile*>>& content = map.getContent();
    sf::Image map_image;
    map_image.create(MAP_SIZE * TILE_WIDTH,MAP_SIZE * TILE_HEIGTH);
    sf::Color color = sf::Color(255,255,255);
    map_image.setPixel(0,0,color);
    for(int i = 0; i < MAP_SIZE; i++) {
        for(int j = 0; j < MAP_SIZE; j++) {
            //right for every i
            //left and down for every j
            //rest is adjusting
            int x = TILE_WIDTH/2*i - TILE_WIDTH/2*j + (MAP_SIZE * TILE_WIDTH)/2 - TILE_WIDTH/2;
            int y = TILE_HEIGTH/2*i + TILE_HEIGTH/2*j;
            map_image.copy(content[j][i]->getTileType()->getTileImage(),x,y,sf::IntRect(0, 0, 0, 0),true);
        }
    }
    map_texture.loadFromImage(map_image);
    map_sprite.setTexture(map_texture);
    map_sprite.setPosition(10.f,50.f);
    return true;
}

void Renderer::renderMap(sf::RenderWindow& window, CameraContext& context) {
    window.clear();
    sf::Vector2f pos = context.camera_pos;
    pos.x -= MAP_SIZE * TILE_WIDTH * (context.zoom/2-1);
    pos.y -= MAP_SIZE * TILE_HEIGTH * (context.zoom/2-1);
    map_sprite.setPosition(pos);
    map_sprite.setScale(context.zoom,context.zoom);
    window.draw(map_sprite);
    window.display();
}