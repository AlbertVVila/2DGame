#ifndef _DOOR_INCLUDE
#define _DOOR_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <string.h>

// Door represents the door that gets openen and closed with buttons


class Door
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string file);
	void update(int deltaTime);
	void render();

	void open();
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setTimeOpened(int time);

private:
	glm::ivec2 tileMapDispl, posDoor;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int timeOpened;
	float opened, sound_cd;
};


#endif // _DOOR_INCLUDE