#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Clock.h"
#include "Game.h"

enum ClockAnims
{
	DEFAULT
};

void Clock::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/clock_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(DEFAULT, 8);
	sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));


	sprite->changeAnimation(DEFAULT);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posClock.x), float(tileMapDispl.y + posClock.y)));

}

void Clock::update(int deltaTime)
{
	sprite->update(deltaTime);
	int px = player->getPosition().x;
	int py = player->getPosition().y;
	int sx = posClock.x;
	int sy = posClock.y;
	int anim = sprite->animation();

	if ((py == sy - 8) && (px - sx) >= -16 && (px - sx) < 15)
	{
		player->setPosition(target);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posClock.x), float(tileMapDispl.y + posClock.y)));
}

void Clock::render()
{
	sprite->render();
}

void Clock::setPlayer(Player *p)
{
	player = p;
}

void Clock::setPosition(const glm::vec2 &pos)
{
	posClock = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posClock.x), float(tileMapDispl.y + posClock.y)));
}

void Clock::setTarget(const glm::vec2 &pos)
{
	target = pos;
}