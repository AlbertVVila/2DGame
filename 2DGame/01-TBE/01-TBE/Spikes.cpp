#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Spikes.h"
#include "Game.h"

enum SpikesAnims
{
	IDLE, SPIKING
};

void Spikes::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/spikes_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(SPIKING, 8);
	sprite->addKeyframe(SPIKING, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(SPIKING, glm::vec2(0.1f, 0.0f));
	sprite->addKeyframe(SPIKING, glm::vec2(0.2f, 0.0f));
	sprite->addKeyframe(SPIKING, glm::vec2(0.3f, 0.0f));
	sprite->addKeyframe(SPIKING, glm::vec2(0.4f, 0.0f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSpikes.x), float(tileMapDispl.y + posSpikes.y)));

}

void Spikes::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (Game::instance().getSpecialKey(GLUT_KEY_F2))
	{
		sprite->changeAnimation(SPIKING);
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

void Spikes::setPosition(const glm::vec2 &pos)
{
	posSpikes = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSpikes.x), float(tileMapDispl.y + posSpikes.y)));
}