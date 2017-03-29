#ifndef _SWORD_INCLUDE
#define _SWORD_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include <string.h>

// Sword represent the sword droped that can be taken by the player


class Sword
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPlayer(Player *p);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posSword;
	Texture spritesheet;
	Sprite *sprite;
	Player *player;
};


#endif // _SWORD_INCLUDE