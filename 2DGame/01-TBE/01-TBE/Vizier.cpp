#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Vizier.h"
#include "Game.h"

#define TIME_A 2000

enum VizierAnims
{
	STAND_L, STAND_R, ATTACK_ONE_L, ATTACK_ONE_R, ATTACK_TWO_L, ATTACK_TWO_R,
	ATTACK_THREE_L, ATTACK_THREE_R, WALK_L, WALK_R, DIE_L, DIE_R
};


void Vizier::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/vizier.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(STAND_L, 8);
	sprite->addKeyframe(STAND_L, glm::vec2(0.7f, 0.0f));

	sprite->setAnimationSpeed(STAND_R, 8);
	sprite->addKeyframe(STAND_R, glm::vec2(-0.8f, 0.0f));

	sprite->setAnimationSpeed(ATTACK_ONE_L, 8);
	sprite->addKeyframe(ATTACK_ONE_L, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_L, glm::vec2(0.1f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_L, glm::vec2(0.2f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_L, glm::vec2(0.3f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_L, glm::vec2(0.4f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_L, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(ATTACK_ONE_R, 8);
	sprite->addKeyframe(ATTACK_ONE_R, glm::vec2(-0.1f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_R, glm::vec2(-0.2f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_R, glm::vec2(-0.3f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_R, glm::vec2(-0.4f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_R, glm::vec2(-0.5f, 0.0f));
	sprite->addKeyframe(ATTACK_ONE_R, glm::vec2(-0.6f, 0.0f));

	sprite->setAnimationSpeed(WALK_L, 8);
	sprite->addKeyframe(WALK_L, glm::vec2(0.6f, 0.25f));
	sprite->addKeyframe(WALK_L, glm::vec2(0.7f, 0.25f));
	sprite->addKeyframe(WALK_L, glm::vec2(0.8f, 0.25f));

	sprite->setAnimationSpeed(WALK_R, 8);
	sprite->addKeyframe(WALK_R, glm::vec2(-0.7f, 0.25f));
	sprite->addKeyframe(WALK_R, glm::vec2(-0.8f, 0.25f));
	sprite->addKeyframe(WALK_R, glm::vec2(-0.9f, 0.25f));

	sprite->setAnimationSpeed(DIE_L, 8);
	sprite->addKeyframe(DIE_L, glm::vec2(0.0f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.1f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.2f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.3f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.4f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.5f, 0.75f));

	sprite->setAnimationSpeed(DIE_R, 8);
	sprite->addKeyframe(DIE_L, glm::vec2(-0.1f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(-0.2f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(-0.3f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(-0.4f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(-0.5f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(-0.6f, 0.75f));


	sprite->changeAnimation(STAND_L);
	timeAnim = 0;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posVizier.x), float(tileMapDispl.y + posVizier.y)));

}

void Vizier::update(int deltaTime)
{
	sprite->update(deltaTime);
	int frame = sprite->getFrame();
	switch (sprite->animation()){
	case WALK_L:
		posVizier.x -= 1;
		break;
	case WALK_R:
		posVizier.x += 1;
		break;
	}

	timeAnim += deltaTime;

	if (sprite->animation() == STAND_L && timeAnim >= TIME_A)
	{
		sprite->changeAnimation(WALK_L);
		timeAnim = 0;
	}

	else if (sprite->animation() == WALK_L && sprite->animFinished() && timeAnim >= TIME_A)
	{
		sprite->changeAnimation(STAND_R);
		timeAnim = 0;
	}

	else if (sprite->animation() == STAND_R && timeAnim >= TIME_A)
	{
		sprite->changeAnimation(WALK_R);
		timeAnim = 0;
	}

	else if (sprite->animation() == WALK_R && sprite->animFinished() && timeAnim >= TIME_A)
	{
		sprite->changeAnimation(STAND_L);
		timeAnim = 0;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posVizier.x), float(tileMapDispl.y + posVizier.y)));
}

void Vizier::render()
{
	sprite->render();
}

void Vizier::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Vizier::setPlayer(Player *p)
{
	player = p;
}

void Vizier::setPosition(const glm::vec2 &pos)
{
	posVizier = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posVizier.x), float(tileMapDispl.y + posVizier.y)));
}