#ifndef _LIFE_INCLUDE
#define _LIFE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include <string.h>

// Life represents the amount of life of the player


class Life
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPlayer(Player *p);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posLife;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	Player *player;
};


#endif // _LIFE_INCLUDE