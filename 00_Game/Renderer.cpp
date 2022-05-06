//
// Created by tscharn on 06.05.22.
//

#include "Renderer.h"
#include <Domain.h>

Renderer::Renderer(Map& map) : map(map) {
    generateMap();
}

bool Renderer::generateMap() {
    //muss hier weg
    sf::Image tile1;
    if (!tile1.loadFromFile(textures::tiles + "tile.png")) {
        return -1;
    }
    sf::Image tile2;
    if (!tile2.loadFromFile(textures::tiles + "tile2.png")) {
        return -1;
    }
    // bis hier

    TileNames content[MAP_SIZE][MAP_SIZE];
    map.getContent(content);
    sf::Image map_image;
    map_image.create(MAP_SIZE * TILE_WIDTH,MAP_SIZE * TILE_HEIGTH);
    sf::Color color = sf::Color(255,255,255);
    map_image.setPixel(0,0,color);
    for(int i = 0; i < MAP_SIZE; i++) {
        for(int j = 0; j < MAP_SIZE; j++) {
            int x = TILE_WIDTH/2*i - TILE_WIDTH/2*j + (3 * TILE_WIDTH)/2;
            int y = TILE_HEIGTH/2*i + TILE_HEIGTH/2*j;
            printf("Placing Tile (%d,%d) at %d, %d\n",i,j, x,y);
            if(content[i][j] == 0) {
                map_image.copy(tile1,x,y,sf::IntRect(0, 0, 0, 0),true);
            } else {
                map_image.copy(tile2,x,y,sf::IntRect(0, 0, 0, 0),true);
            }
        }
    }
    sf::Texture texture;
    texture.loadFromImage(map_image);
    map_sprite.setTexture(texture);
    map_sprite.setPosition(10.f,50.f);
    return true;
}

void Renderer::renderMap(sf::RenderWindow& window) {
    window.clear();
    window.draw(map_sprite);
    window.display();
}