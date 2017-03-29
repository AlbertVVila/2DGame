#ifndef _CLOCK_INCLUDE
#define _CLOCK_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include <string.h>

// Clock represents a teleporter.
// Two clocks are always linked: if the player steps
// to one, is teleported to the other


class Clock
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPlayer(Player *p);
	void setPosition(const glm::vec2 &pos);
	void setTarget(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posClock;
	Texture spritesheet;
	Sprite *sprite;
	Player *player;
	glm::vec2 target;
};


#endif // _CLOCK_INCLUDE