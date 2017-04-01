#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Life.h"
#include "Game.h"

enum LifeAnims
{
	ZERO, ONE, TWO, THREE
};


void Life::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/player_life.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(320, 64), glm::vec2(1, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(THREE, 8);
	sprite->addKeyframe(THREE, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(TWO, 8);
	sprite->addKeyframe(TWO, glm::vec2(0.0f, 0.25f));

	sprite->setAnimationSpeed(ONE, 8);
	sprite->addKeyframe(ONE, glm::vec2(0.0f, 0.5f));

	sprite->setAnimationSpeed(ZERO, 8);
	sprite->addKeyframe(ZERO, glm::vec2(0.0f, 0.75f));


	sprite->changeAnimation(THREE);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posLife.x), float(tileMapDispl.y + posLife.y)));
}

void Life::update(int deltaTime)
{
	sprite->update(deltaTime);
	int frame = sprite->getFrame();
	int px = player->getPosition().x;
	int py = player->getPosition().y;
	int lx = posLife.x;
	int ly = posLife.y;
	int anim = sprite->animation();

	if (sprite->animation() != ZERO && player->getHP() == 0) sprite->changeAnimation(ZERO);
	if (sprite->animation() != ONE && player->getHP() == 1) sprite->changeAnimation(ONE);
	if (sprite->animation() != TWO && player->getHP() == 2) sprite->changeAnimation(TWO);
	if (sprite->animation() != THREE && player->getHP() == 3) sprite->changeAnimation(THREE);

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posLife.x), float(tileMapDispl.y + posLife.y)));
}

void Life::render()
{
	sprite->render();
}

void Life::setPlayer(Player *p)
{
	player = p;
}

void Life::setPosition(const glm::vec2 &pos)
{
	posLife = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posLife.x), float(tileMapDispl.y + posLife.y)));
}