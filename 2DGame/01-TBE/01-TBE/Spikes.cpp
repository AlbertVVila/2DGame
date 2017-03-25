#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Spikes.h"
#include "Game.h"

enum SpikesAnims
{
	DOWN, GOUP, UP, GODOWN
};

void Spikes::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/spikes_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(DOWN, 8);
	sprite->addKeyframe(DOWN, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(UP, 8);
	sprite->addKeyframe(UP, glm::vec2(0.4f, 0.0f));

	sprite->setAnimationSpeed(GOUP, 8);
	sprite->addKeyframe(GOUP, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.1f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.2f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.3f, 0.0f));
	sprite->addKeyframe(GOUP, glm::vec2(0.4f, 0.0f));

	sprite->setAnimationSpeed(GODOWN, 8);
	sprite->addKeyframe(GODOWN, glm::vec2(0.4f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.3f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.2f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.1f, 0.0f));
	sprite->addKeyframe(GODOWN, glm::vec2(0.0f, 0.0f));


	sprite->changeAnimation(DOWN);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSpikes.x), float(tileMapDispl.y + posSpikes.y)));

}

void Spikes::update(int deltaTime)
{
	sprite->update(deltaTime);
	int px = player->getPosition().x;
	int py = player->getPosition().y;
	int sx = posSpikes.x;
	int sy = posSpikes.y;
	int anim = sprite->animation();

	if (Game::instance().getSpecialKey(GLUT_KEY_F2))
	{
		sprite->changeAnimation(GOUP);
	}

	if (anim == DOWN && (py == sy - 8) && (px - sx) >= -16 && (px - sx) < 15)
	{
		sprite->changeAnimation(GOUP);
	}

	if (anim == GOUP && sprite->animFinished())
	{
		sprite->changeAnimation(UP);
	}

	if (anim == UP && ((py != sy - 8) || (px - sx) < -16 || (px - sx) >= 15))
	{
		sprite->changeAnimation(GODOWN);
	}

	if (anim == GODOWN && sprite->animFinished())
	{
		sprite->changeAnimation(DOWN);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSpikes.x), float(tileMapDispl.y + posSpikes.y)));
}

void Spikes::render()
{
	sprite->render();
}

void Spikes::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Spikes::setPlayer(Player *p)
{
	player = p;
}

void Spikes::setPosition(const glm::vec2 &pos)
{
	posSpikes = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSpikes.x), float(tileMapDispl.y + posSpikes.y)));
}