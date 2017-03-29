#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Sword.h"
#include "Game.h"

enum SwordAnims
{
	DOWN, TAKEN
};

void Sword::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/sword_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(DOWN, 8);
	sprite->addKeyframe(DOWN, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(TAKEN, 8);
	sprite->addKeyframe(TAKEN, glm::vec2(0.5f, 0.0f));


	sprite->changeAnimation(DOWN);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSword.x), float(tileMapDispl.y + posSword.y)));

}

void Sword::update(int deltaTime)
{
	sprite->update(deltaTime);
	int px = player->getPosition().x;
	int py = player->getPosition().y;
	int sx = posSword.x;
	int sy = posSword.y;
	int anim = sprite->animation();

	if (anim == DOWN && (py == sy - 8) && (px - sx) >= -16 && (px - sx) < 15 && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		sprite->changeAnimation(TAKEN);
		player->getSword();
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSword.x), float(tileMapDispl.y + posSword.y)));
}

void Sword::render()
{
	sprite->render();
}

void Sword::setPlayer(Player *p)
{
	player = p;
}

void Sword::setPosition(const glm::vec2 &pos)
{
	posSword = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSword.x), float(tileMapDispl.y + posSword.y)));
}