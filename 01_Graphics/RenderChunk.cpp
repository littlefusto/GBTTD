//
// Created by rriigg on 31.05.23.
//

#include <gbttd.h>
//!!!!!!!!!!!!!!!!!!!!!!!!!!
// TODO: Rendering should be reverted to squares making use of the alpha of the tile.
// Reason: Retains all pixel edges and prevents straight edges
// Disadvantage: Probably slower since more overdraw.
RenderChunk::RenderChunk(Map &map, unsigned int cx, unsigned cy): map(map) {
    this->chunkPos = sf::Vector2i(cx, cy);
    TextureHandler* textureHandler = TextureHandler::getInstance();
    tileset = textureHandler->getTextureAtlas();
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(CHUNK_SIZE * CHUNK_SIZE * 4);
    std::vector<std::vector<Tile*>>& content = map.getContent();
    updateMesh();
}

RenderChunk::~RenderChunk() {
    // TODO: Don't know if any cleanup is needed since sfml should do most of it
}

void RenderChunk::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = tileset;

    // draw the vertex array
    target.draw(vertices, states);
}

void RenderChunk::updateMesh() {
    TextureHandler* textureHandler = TextureHandler::getInstance();
    std::vector<std::vector<Tile*>>& content = map.getContent();
    // populate the vertex array, with one quad per tile
    for (int y = 0; y < CHUNK_SIZE; ++y) {
        int ox = -y * TILE_WIDTH / 2;
        int oy = y * TILE_HEIGHT / 2;
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &vertices[(x + y * CHUNK_SIZE) * 4];
            Tile* tile = content[chunkPos.y * CHUNK_SIZE + y][chunkPos.x * CHUNK_SIZE + x];
            textureInfo& textureInfo = textureHandler->getTextureByTileType(tile);
            // define its 4 corners
            // top left, top right, bottom right, bottom left
            char tileHeight = tile->getHeight();
            quad[0].position = sf::Vector2f(ox - TILE_WIDTH / 2, oy - TILE_HEIGHT / 2 - tileHeight * 8);
            quad[1].position = sf::Vector2f(ox + TILE_WIDTH / 2, oy - TILE_HEIGHT / 2 - tileHeight * 8);
            quad[2].position = sf::Vector2f(ox + TILE_WIDTH / 2, oy + TILE_HEIGHT + TILE_HEIGHT / 2 - tileHeight * 8);
            quad[3].position = sf::Vector2f(ox - TILE_WIDTH / 2, oy + TILE_HEIGHT + TILE_HEIGHT / 2 - tileHeight * 8);
            sf::Vector2f tileTextureOffset(tile->getTileSlope() * TILE_WIDTH, tile->getTileType() * TILE_HEIGHT * 2);
            // define its 4 texture coordinates
            quad[0].texCoords = tileTextureOffset + sf::Vector2f(0, 0);
            quad[1].texCoords = tileTextureOffset + sf::Vector2f(TILE_WIDTH, 0);
            quad[2].texCoords = tileTextureOffset + sf::Vector2f(TILE_WIDTH, 2 * TILE_HEIGHT);
            quad[3].texCoords = tileTextureOffset + sf::Vector2f(0, 2 * TILE_HEIGHT);

            // move diagonally down to the right
            ox += TILE_WIDTH / 2;
            oy += TILE_HEIGHT / 2;
        }
    }
}