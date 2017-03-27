#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Falling.h"
#include "Game.h"

#define SHAKE_TIME 1000

enum FallingAnims
{
	IDLE, FALLING, FELL
};

void Falling::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/falling_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(FALLING, 8);
	sprite->addKeyframe(FALLING, glm::vec2(0.1f, 0.0f));
	sprite->addKeyframe(FALLING, glm::vec2(0.2f, 0.0f));

	sprite->setAnimationSpeed(FELL, 8);
	sprite->addKeyframe(FELL, glm::vec2(0.3f, 0.0f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFalling.x), float(tileMapDispl.y + posFalling.y)));

}

void Falling::update(int deltaTime)
{
	sprite->update(deltaTime);
	int px = player->getPosition().x;
	int py = player->getPosition().y;
	int fx = posFalling.x;
	int fy = posFalling.y;

	if (Game::instance().getSpecialKey(GLUT_KEY_F1))
	{
		sprite->changeAnimation(FALLING);
		time_shaking = 0;
	}
	else if (sprite->animation() == IDLE && (py == fy - 8) && (px - fx) >= -27 && (px - fx) < 15)
	{
		sprite->changeAnimation(FALLING);
		time_shaking = 0;
	}
	else if (sprite->animation() == FALLING)
	{
		time_shaking += deltaTime;
		if (time_shaking >= SHAKE_TIME)
			posFalling.y += 4;
		if (map->collisionMoveDown(posFalling, glm::ivec2(32, 64), &posFalling.y))
		{
			sprite->changeAnimation(FELL);
			posFalling.y += 8;
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFalling.x), float(tileMapDispl.y + posFalling.y)));
}

void Falling::render()
{
	sprite->render();
}

void Falling::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Falling::setPlayer(Player *p)
{
	player = p;
}

void Falling::setPosition(const glm::vec2 &pos)
{
	posFalling = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFalling.x), float(tileMapDispl.y + posFalling.y)));
}