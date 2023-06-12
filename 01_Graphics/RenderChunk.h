//
// Created by rriigg on 31.05.23
//

#pragma once

#include <gbttd.h>

class RenderChunk: public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray vertices;
    sf::Texture* tileset;
    Map* map;

    sf::Vector2i chunkPos;
	
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    RenderChunk(Map* map, unsigned int cx, unsigned int cy);
    ~RenderChunk();

    void updateMesh();
};
