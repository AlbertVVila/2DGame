#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Door.h"
#include "Game.h"

#define TIME_OPENED 5000

enum DoorAnims
{
	DOWN, UP, GOUP, GODOWN
};

void Door::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/door_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
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
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));

}

void Door::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (sprite->animation() == GOUP && sprite->animFinished())
	{
		sprite->changeAnimation(UP);
		opened = 0;
	}
	if (sprite->animation() == UP)
	{
		opened += deltaTime;
		if (opened >= TIME_OPENED)
			sprite->changeAnimation(GODOWN);
	}
	if (sprite->animation() == GODOWN && sprite->animFinished())
		sprite->changeAnimation(DOWN);

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
}