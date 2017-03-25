#ifndef _SPIKES_INCLUDE
#define _SPIKES_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include <string.h>

// Spikes represents a trap where the player dies


class Spikes
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPlayer(Player *p);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posSpikes;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	Player *player;
};


#endif // _SPIKES_INCLUDE