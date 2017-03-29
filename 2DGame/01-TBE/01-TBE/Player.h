#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <string.h>

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	glm::vec2 getPosition();
	int getHP();
	bool isDead();
	bool isAttacking();
	bool isAttackingLong();
	bool isBlocking();
	void damage(int amount, string type);
	void heal(int amount);
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setCombat(bool combat);

private:
	bool bCombat, dead;
	int hp;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	bool teEspasa;

};


#endif // _PLAYER_INCLUDE