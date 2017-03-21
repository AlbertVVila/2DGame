#ifndef _SPIKES_INCLUDE
#define _SPIKES_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <string.h>

// Falling represents a falling ground (falls when player steps over)


class Spikes
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posSpikes;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};


#endif // _SPIKES_INCLUDE