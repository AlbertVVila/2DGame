#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Button.h"
#include "Game.h"

enum ButtonAnims
{
	DOWN, UP
};

void Button::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string file)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile(file, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(DOWN, 8);
	sprite->addKeyframe(DOWN, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(UP, 8);
	sprite->addKeyframe(UP, glm::vec2(0.1f, 0.0f));

	sprite->changeAnimation(UP);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));

}

void Button::update(int deltaTime)
{
	sprite->update(deltaTime);
	int px = player->getPosition().x;
	int py = player->getPosition().y;
	int bx = posButton.x;
	int by = posButton.y;
	int anim = sprite->animation();

	if (anim == UP && (py == by - 8) && (px - bx) >= -27 && (px - bx) < 15 && !player->isJumping())
	{
		sprite->changeAnimation(DOWN);
		door->open();
	}
	if (anim == DOWN && ((py != by - 8) || (px - bx) < -27 || (px - bx) >= 15))
	{
		sprite->changeAnimation(UP);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}

void Button::render()
{
	sprite->render();
}

void Button::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Button::setPosition(const glm::vec2 &pos)
{
	posButton = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}

void Button::setDoor(Door *d)
{
	door = d;
}

void Button::setPlayer(Player *p)
{
	player = p;
}