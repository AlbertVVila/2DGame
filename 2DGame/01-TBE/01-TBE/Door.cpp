#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Door.h"
#include "Game.h"
#include "windows.h"
#include "mmsystem.h"

#define TIME_OPENED 5000

enum DoorAnims
{
	DOWN, UP, GOUP, GODOWN
};

void Door::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string file)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile(file, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(DOWN, 4);
	sprite->addKeyframe(DOWN, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(UP, 4);
	sprite->addKeyframe(UP, glm::vec2(0.7f, 0.0f));

	sprite->setAnimationSpeed(GOUP, 4);
	sprite->addKeyframe(GOUP, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.1f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.2f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.3f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.4f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.6f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.7f, 0.0f));

	sprite->setAnimationSpeed(GODOWN, 4);
	sprite->addKeyframe(GODOWN, glm::vec2(0.7f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.6f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.4f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.3f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.2f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.1f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.0f, 0.0f));


	sprite->changeAnimation(0);
	timeOpened = 5000;
	sound_cd = 0;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));

}

void Door::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (sprite->animation() == GOUP)
	{
		sound_cd += deltaTime;
		if (sound_cd >= 200) { sound_cd = 0; PlaySound(TEXT("music/door_moving.wav"), NULL, SND_ASYNC); }
		if (sprite->getFrame()==2)map->deleteTrapCollider(tileMapDispl.x + posDoor.x, tileMapDispl.y + posDoor.y);
		else if (sprite->animFinished()){
				sprite->changeAnimation(UP);
				opened = 0;
		}
	}
	if (sprite->animation() == UP)
	{
		opened += deltaTime;
		if (opened >= timeOpened)
			sprite->changeAnimation(GODOWN);
	}
	if (sprite->animation() == GODOWN){
		sound_cd += deltaTime;
		if (sound_cd >= 200) { sound_cd = 0; PlaySound(TEXT("music/door_moving.wav"), NULL, SND_ASYNC); }
		if (sprite->getFrame()==2) map->newTrapCollider(tileMapDispl.x + posDoor.x, tileMapDispl.y + posDoor.y, 2);
		else if (sprite->animFinished()){
			sprite->changeAnimation(DOWN);
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));
}

void Door::render()
{
	sprite->render();
}

void Door::open()
{
	if (sprite->animation() == DOWN)
		sprite->changeAnimation(GOUP);
}

void Door::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Door::setPosition(const glm::vec2 &pos)
{
	posDoor = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));
	map->newTrapCollider(tileMapDispl.x + posDoor.x, tileMapDispl.y + posDoor.y, 2);
}

void Door::setTimeOpened(int time)
{
	timeOpened = time;
}
