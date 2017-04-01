#ifndef _FAT_INCLUDE
#define _FAT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include <string.h>

// Fat represents a simple enemy that can walk,
// attack or defend, and die to player attacks.


class Fat
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPlayer(Player *p);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posFat;
	Texture spritesheet, lifesheet;
	Sprite *sprite, *star, *life;
	TileMap *map;
	Player *player;
	float health;
	int frameant;
	float cd, cd_damage, cd_star;
	bool bloked;
	int strike;
};


#endif // _FAT_INCLUDE