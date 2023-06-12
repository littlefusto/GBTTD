//
// Created by cpukiller on 06.05.22.
//
#include <gbttd.h>

Renderer::Renderer(Map* map) : map(map) {
	pointAt = sf::Vector2i(0, 0);
	selectedTile = sf::Vector2i(-1, -1);
	selectedTileImage = TextureHandler::getInstance()->getImage("selectedTile.png");
	mapChunks = std::vector<std::vector<RenderChunk*>>((int) ceil(map->getSize().y / CHUNK_SIZE));
	for (int y = 0; y < mapChunks.size(); y++) {
		mapChunks[y] = std::vector<RenderChunk*>((int) ceil(map->getSize().x / CHUNK_SIZE));
		for (int x = 0; x < mapChunks[y].size(); x++) {
			mapChunks[y][x] = nullptr;
		}
	}
	generateMap();
	// load font
	if (!defaultFont.loadFromFile(BASE_FONT)) {
		printf("No font found at the provided path: '%s'\n", BASE_FONT);
		exit(-1);
	}
	lastFrame = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
	fpsText = sf::Text("0", defaultFont, 30);
	fpsText.setFillColor(sf::Color(255, 255, 255, 255));
	fpsText.setOutlineColor(sf::Color());
	fpsText.setPosition(0, 0);
	printf("Renderer init complete\n");
}

void Renderer::deleteChunks() {
	for (int y = 0; y < mapChunks.size(); y++) {
		for (int x = 0; x < mapChunks[y].size(); x++) {
			if (mapChunks[y][x] != nullptr) {
				RenderChunk* chunk = mapChunks[y][x];
				delete chunk;
			}
		}
	}
	mapChunks.clear();
}

Renderer::~Renderer() {
	deleteChunks();
}

bool Renderer::generateMap() {
	std::vector<std::vector<Tile*>> &content = map->getContent();
	TextureHandler *textureHandler = TextureHandler::getInstance();
	Vector2i renderChunkSize(CHUNK_SIZE * TILE_WIDTH, CHUNK_SIZE * TILE_HEIGHT);

	for (int y = 0; y < mapChunks.size(); y++) {
		int px = -y * renderChunkSize.x / 2;
		int py = y * renderChunkSize.y / 2;
		for (int x = 0; x < mapChunks[y].size(); x++) {
			mapChunks[y][x] = new RenderChunk(map, x, y);
			mapChunks[y][x]->setPosition(px, py);
			px += renderChunkSize.x / 2;
			py += renderChunkSize.y / 2;
		}
	}
	printf("Generated Chunks.\n");
	return true;
}

template<typename T>
double length(const sf::Vector2<T> &a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

template<typename T>
double dot(const sf::Vector2<T> &a, const sf::Vector2<T> &b) {
	return a.x * b.x + a.y * b.y;
}

double calculateDistance(Vector2i &a, Vector2i &b) {
	return length(a-b);
}

int calculateSquaredDistance(Vector2i &a, Vector2i &b) {
	return dot(a, b);
}

void Renderer::updateMap() {
	updateRect(0, 0, map->getSize().x, map->getSize().y);
}

void Renderer::updateRect(int x, int y, int width, int height) {
	int cx = x / CHUNK_SIZE;
	int cy = y / CHUNK_SIZE;
	int cmx = (x+width) / CHUNK_SIZE;
	int cmy = (y+height) / CHUNK_SIZE;
	if (cmy >= mapChunks.size()) cmy = mapChunks.size() - 1;
	if (cmx >= mapChunks[0].size()) cmx = mapChunks[0].size() - 1;
	if (cx < 0) cx = 0;
	if (cy < 0) cy = 0;
	for (int py = cy; py <= cmy; py++) {
		for (int px = cx; px <= cmx; px++) {
			mapChunks[py][px]->updateMesh();
		}
	}
}

void Renderer::renderMap(sf::RenderWindow &window) {
	std::chrono::milliseconds curTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
	float fps = 1000.0f / (curTime - lastFrame).count();
	lastFrame = curTime;
	window.clear();
	sf::View curView = window.getView();
	sf::Vector2f viewCenter = window.getView().getCenter();
	sf::Vector2f viewSize = window.getView().getSize();
	
	sf::Vector2f topRight = worldToMapPos(sf::Vector2f(viewCenter.x + viewSize.x / 2, viewCenter.y - viewSize.y / 2)) * (1 / (float) CHUNK_SIZE);
	sf::Vector2f bottomLeft = worldToMapPos(sf::Vector2f(viewCenter.x - viewSize.x / 2, viewCenter.y + viewSize.y / 2)) * (1 / (float) CHUNK_SIZE);
	float leftViewEdge = viewCenter.x - viewSize.x / 2 - CHUNK_SIZE * TILE_WIDTH / 2;
	float rightViewEdge = viewCenter.x + viewSize.x / 2 + CHUNK_SIZE * TILE_WIDTH / 2;

	// Only draw chunks which are visible.
	// Iterates diagonals top left to bottom right diagonals starting at the top right corner of the viewing rectangle.
	int startX = (int) topRight.x - 1;
	int endX = (int)(viewSize.y / TILE_HEIGHT / CHUNK_SIZE * 2) + 4 + startX;
	for (int y = (int) floor(topRight.y); y < (int) mapChunks.size() && y < bottomLeft.y; y++) {
		for (int x = max(startX, 0); x < mapChunks[y].size() && x < endX && y >= 0; x++) {
			float chunkLeft = mapToWorldPos(sf::Vector2f(x * CHUNK_SIZE, y * CHUNK_SIZE)).x;
			if (chunkLeft < leftViewEdge) continue;
			if (chunkLeft > rightViewEdge) break;
			window.draw(*mapChunks[y][x]);
		}
		startX--;
		endX--;
	}
	// draw "gui"/fps counter for now
	window.setView(window.getDefaultView());
	fpsText.setString(to_string((int)fps));
	window.draw(fpsText);
	window.setView(curView);
	
	window.display();
	//exit(0);
}

/**
* Calculates the area of the parallelogram of the three points.
* This is actually the same as the area of the triangle defined by the three points, multiplied by 2.
* @return 2 * triangleArea(a,b,c)
*/
int perpDotProduct(sf::Vector2i a, sf::Vector2i b, sf::Vector2i c) {
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}

sf::Vector2f Renderer::worldToMapPos(sf::Vector2f worldPos) {
	return sf::Vector2f(worldPos.x/TILE_WIDTH + worldPos.y/TILE_HEIGHT, worldPos.y/TILE_HEIGHT - worldPos.x/TILE_WIDTH);
}

sf::Vector2f Renderer::mapToWorldPos(sf::Vector2f mapPos) {
	return sf::Vector2f((mapPos.x - mapPos.y)*TILE_WIDTH/2, (mapPos.x + mapPos.y)*TILE_HEIGHT/2);
}

sf::Vector2i Renderer::getClickedTile(sf::Vector2f worldPos) {
	// TODO: maybe use vertex function and then determine which adjacent tile is clicked
	return sf::Vector2i(0,0);
}

sf::Vector2i Renderer::getClickedVertex(sf::Vector2f worldPos) {
	sf::Vector2f mapPos = worldToMapPos(worldPos);
	// Determine the vertical collumn of vertices
	// These vertices lie on a diagonal in map coordinates but a straight column in world coordinates
	sf::Vector2i curMapPos((int) floor(mapPos.x), (int) floor(mapPos.y));
	sf::Vector2f curWorldPos = mapToWorldPos((sf::Vector2f) curMapPos);
	if (abs(curWorldPos.x - worldPos.x)
		> abs(mapToWorldPos(sf::Vector2f(floor(mapPos.x), floor(mapPos.y) + 1)).x - worldPos.x))
	{
		curMapPos = sf::Vector2i((int) mapPos.x, (int) mapPos.y + 1);
	}
	// Start position might lie outside of the map. First move to the edge of the map.
	if (curMapPos.x - curMapPos.y >= map->getSize().x) {
		curMapPos = sf::Vector2i(map->getSize().x, 0);
	} else if (curMapPos.y - curMapPos.x >= map->getSize().y) {
		curMapPos = sf::Vector2i(0, map->getSize().y);
	}
	int distToMap = min(curMapPos.x, curMapPos.y);
	if (distToMap < 0) {
		curMapPos += sf::Vector2i(-distToMap, -distToMap);
	}
	distToMap = max(curMapPos.x - map->getSize().x, curMapPos.y - map->getSize().y);
	if (distToMap > 0) {
		return curMapPos - sf::Vector2i(distToMap, distToMap);
	}
	curWorldPos = mapToWorldPos((sf::Vector2f) curMapPos);
	// Scince the terrain is not flat the determined positioned coordinates might be wrong.
	// Nevertheless, for a "collumn" of vertices the world x position is the same.
	// Because of this, we can move down the collumn until we find the closest vertex.
	float minDist = worldPos.y - curWorldPos.y + map->getHeight(curMapPos.x, curMapPos.y) * 8;
	int bestY = 0;
	for (int i = 1; i < MAX_MAP_HEIGHT; i++) {
		if (curMapPos.x+i > map->getSize().x || curMapPos.y+i > map->getSize().y) break;
		float curDist = abs(curWorldPos.y + i * TILE_HEIGHT - map->getHeight(curMapPos.x + i, curMapPos.y + i) * 8 - worldPos.y);
		if (curDist < minDist) {
			minDist = curDist;
			bestY = i;
		} else {
			break;
		}
	}
	curMapPos += sf::Vector2i(bestY, bestY);
	return curMapPos;
}

void Renderer::setMap(Map* map) {
	this->map = map;
	this->deleteChunks();
	mapChunks = std::vector<std::vector<RenderChunk*>>((int) ceil(map->getSize().y / CHUNK_SIZE));
	for (int y = 0; y < mapChunks.size(); y++) {
		mapChunks[y] = std::vector<RenderChunk*>((int) ceil(map->getSize().x / CHUNK_SIZE));
	}
	this->generateMap();
}