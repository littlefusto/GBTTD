//
// Created by rriigg on 31.05.23.
//

#include <gbttd.h>
#include <vector>

RenderChunk::RenderChunk(Map &map, unsigned int cx, unsigned cy) {
    tileset = TextureHandler::getInstance()->getTextureAtlas();
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(CHUNK_SIZE * CHUNK_SIZE * 4);
    std::vector<std::vector<Tile*>>& content = map.getContent();

    // populate the vertex array, with one quad per tile
    for (int y = 0; y < CHUNK_SIZE; ++y) {
        int ox = -y * TILE_WIDTH / 2;
        int oy = y * TILE_HEIGHT / 2;
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &vertices[(x + y * CHUNK_SIZE) * 4];
            Tile* tile = content[cy * CHUNK_SIZE + y][cx * CHUNK_SIZE + x];
            int height = 8 * tile->getHeight();
            if (height > 8) {
                printf("Height: %d\n", height);
            }
            // define its 4 corners
            quad[0].position = sf::Vector2f(ox - TILE_WIDTH / 2, oy - TILE_HEIGHT - height);
            quad[1].position = sf::Vector2f(ox + TILE_WIDTH / 2, oy - TILE_HEIGHT - height);
            quad[2].position = sf::Vector2f(ox + TILE_WIDTH / 2, oy + TILE_HEIGHT - height);
            quad[3].position = sf::Vector2f(ox - TILE_WIDTH / 2, oy + TILE_HEIGHT - height);
            // printf("Bottom right: (%f, %f)\n", quad[2].position.x, quad[3].position.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tile->getTileSlope() * TILE_WIDTH, tile->getTileType() * TILE_HEIGHT * 2);
            quad[1].texCoords = sf::Vector2f((tile->getTileSlope() + 1) * TILE_WIDTH, tile->getTileType() * TILE_HEIGHT * 2);
            quad[2].texCoords = sf::Vector2f((tile->getTileSlope() + 1) * TILE_WIDTH, (tile->getTileType() + 1) * TILE_HEIGHT * 2);
            quad[3].texCoords = sf::Vector2f(tile->getTileSlope() * TILE_WIDTH, (tile->getTileType() + 1) * TILE_HEIGHT * 2);
            //printf("Bottom right: (%f, %f)\n", quad[2].texCoords.x, quad[3].texCoords.y);

            ox += TILE_WIDTH / 2;
            oy += TILE_HEIGHT / 2;
        }
    }
}

RenderChunk::~RenderChunk() {

}

void RenderChunk::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = tileset;

    // draw the vertex array
    target.draw(vertices, states);
}