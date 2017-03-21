#ifndef _FALLING_INCLUDE
#define _FALLING_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <string.h>

// Falling represents a falling ground (falls when player steps over)


class Falling
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posFalling;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	float time_shaking;
};


#endif // _FALLING_INCLUDE