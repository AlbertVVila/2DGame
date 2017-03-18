#ifndef _TORCH_INCLUDE
#define _TORCH_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <string.h>

// Torch represents the torches with light in the walls


class Torch
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posTorch;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};


#endif // _TORCH_INCLUDE