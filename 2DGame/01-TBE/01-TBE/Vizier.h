#ifndef _VIZIER_INCLUDE
#define _VIZIER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include <string.h>

// Vizier represents a simple enemy that can walk,
// attack or defend, and die to player attacks.


class Vizier
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPlayer(Player *p);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posVizier;
	Texture spritesheet;
	Sprite *sprite, *star;
	TileMap *map;
	Player *player;
	float health;
	int frameant;
	float cd, cd_damage, cd_star;
	bool bloked;
};


#endif // _VIZIER_INCLUDE