#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Potion.h"
#include "Game.h"

enum PotionAnims
{
	DOWN, TAKEN
};

void Potion::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/potion_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(DOWN, 8);
	sprite->addKeyframe(DOWN, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(TAKEN, 8);
	sprite->addKeyframe(TAKEN, glm::vec2(0.1f, 0.0f));


	sprite->changeAnimation(DOWN);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPotion.x), float(tileMapDispl.y + posPotion.y)));

}

void Potion::update(int deltaTime)
{
	sprite->update(deltaTime);
	int px = player->getPosition().x;
	int py = player->getPosition().y;
	int sx = posPotion.x;
	int sy = posPotion.y;
	int anim = sprite->animation();

	if (anim == DOWN && (py == sy - 8) && (px - sx) >= -16 && (px - sx) < 15 && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		sprite->changeAnimation(TAKEN);
		player->getPotion();
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPotion.x), float(tileMapDispl.y + posPotion.y)));
}

void Potion::render()
{
	sprite->render();
}

void Potion::setPlayer(Player *p)
{
	player = p;
}

void Potion::setPosition(const glm::vec2 &pos)
{
	posPotion = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPotion.x), float(tileMapDispl.y + posPotion.y)));
}