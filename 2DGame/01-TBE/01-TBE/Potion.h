#ifndef _POTION_INCLUDE
#define _POTION_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include <string.h>

// Potion represents a potion that can drink the player to restore health


class Potion
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPlayer(Player *p);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posPotion;
	Texture spritesheet;
	Sprite *sprite;
	Player *player;
};


#endif // _POTION_INCLUDE