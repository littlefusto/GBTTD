//
// Created by rriigg on 31.05.23
//

#ifndef GBTTD_RENDERCHUNK_H
#define GBTTD_RENDERCHUNK_H

#include <gbttd.h>

class RenderChunk: public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray vertices;
    sf::Texture* tileset;
	
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    RenderChunk(Map &map, unsigned int cx, unsigned int cy);
    ~RenderChunk();

};


#endif //GBTTD_RENDERCHUNK_H
