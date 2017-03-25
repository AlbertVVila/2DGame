#ifndef _BUTTON_INCLUDE
#define _BUTTON_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include "Door.h"
#include <string.h>

// Button represents the elevated ground that a player can step to activate a door


class Button
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setPlayer(Player *p);
	void setDoor(Door *d);

private:
	glm::ivec2 tileMapDispl, posButton;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	Door *door;
	Player *player;
};


#endif // _BUTTON_INCLUDE