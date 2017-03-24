#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Vizier.h"
#include "Game.h"

#define TIME_A 2000
#define VISION_RANGE 32 * 5
#define ATTACK_RANGE 32 * 1 + 10

enum VizierAnims
{
	STAND_L, STAND_R,
	WALK_L, WALK_R,
	ATTACK_L, ATTACK_R,
	DIE_L, DIE_R,
	DEAD_L, DEAD_R
};


void Vizier::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/vizier.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(STAND_L, 8);
	sprite->addKeyframe(STAND_L, glm::vec2(0.6f, 0.25f));

	sprite->setAnimationSpeed(STAND_R, 8);
	sprite->addKeyframe(STAND_R, glm::vec2(-0.7f, 0.25f));

	sprite->setAnimationSpeed(WALK_L, 8);
	sprite->addKeyframe(WALK_L, glm::vec2(0.6f, 0.25f));
	sprite->addKeyframe(WALK_L, glm::vec2(0.7f, 0.25f));
	sprite->addKeyframe(WALK_L, glm::vec2(0.8f, 0.25f));

	sprite->setAnimationSpeed(WALK_R, 8);
	sprite->addKeyframe(WALK_R, glm::vec2(-0.7f, 0.25f));
	sprite->addKeyframe(WALK_R, glm::vec2(-0.8f, 0.25f));
	sprite->addKeyframe(WALK_R, glm::vec2(-0.9f, 0.25f));

	sprite->setAnimationSpeed(ATTACK_L, 8);
	sprite->addKeyframe(ATTACK_L, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(ATTACK_L, glm::vec2(0.1f, 0.0f));
	sprite->addKeyframe(ATTACK_L, glm::vec2(0.2f, 0.0f));
	sprite->addKeyframe(ATTACK_L, glm::vec2(0.3f, 0.0f));
	sprite->addKeyframe(ATTACK_L, glm::vec2(0.4f, 0.0f));
	sprite->addKeyframe(ATTACK_L, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(ATTACK_R, 8);
	sprite->addKeyframe(ATTACK_R, glm::vec2(-0.1f, 0.0f));
	sprite->addKeyframe(ATTACK_R, glm::vec2(-0.2f, 0.0f));
	sprite->addKeyframe(ATTACK_R, glm::vec2(-0.3f, 0.0f));
	sprite->addKeyframe(ATTACK_R, glm::vec2(-0.4f, 0.0f));
	sprite->addKeyframe(ATTACK_R, glm::vec2(-0.5f, 0.0f));
	sprite->addKeyframe(ATTACK_R, glm::vec2(-0.6f, 0.0f));

	sprite->setAnimationSpeed(DIE_L, 8);
	sprite->addKeyframe(DIE_L, glm::vec2(0.0f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.1f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.2f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.3f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.4f, 0.75f));
	sprite->addKeyframe(DIE_L, glm::vec2(0.5f, 0.75f));

	sprite->setAnimationSpeed(DIE_R, 8);
	sprite->addKeyframe(DIE_R, glm::vec2(-0.1f, 0.75f));
	sprite->addKeyframe(DIE_R, glm::vec2(-0.2f, 0.75f));
	sprite->addKeyframe(DIE_R, glm::vec2(-0.3f, 0.75f));
	sprite->addKeyframe(DIE_R, glm::vec2(-0.4f, 0.75f));
	sprite->addKeyframe(DIE_R, glm::vec2(-0.5f, 0.75f));
	sprite->addKeyframe(DIE_R, glm::vec2(-0.6f, 0.75f));

	sprite->setAnimationSpeed(DEAD_L, 8);
	sprite->addKeyframe(DEAD_L, glm::vec2(0.5f, 0.75f));

	sprite->setAnimationSpeed(DEAD_R, 8);
	sprite->addKeyframe(DEAD_R, glm::vec2(-0.6f, 0.75f));


	sprite->changeAnimation(STAND_L);
	health = 3;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posVizier.x), float(tileMapDispl.y + posVizier.y)));

}

void Vizier::update(int deltaTime)
{
	sprite->update(deltaTime);
	int frame = sprite->getFrame();
	int px = player->getPosition().x;
	int py = player->getPosition().y;
	int vx = posVizier.x;
	int vy = posVizier.y;
	int anim = sprite->animation();

	switch (anim){
		case WALK_L:
			if(frame == 2) posVizier.x -= 1;
			break;
		case WALK_R:
			if (frame == 2) posVizier.x += 1;
			break;
		default:
			break;
	}

	if ((anim == STAND_L || anim == ATTACK_L) && px > vx)		//Look right
	{
		sprite->changeAnimation(STAND_R);
	}

	if ((anim == STAND_R || anim == ATTACK_R) && px < vx)		//Look left
	{
		sprite->changeAnimation(STAND_L);
	}

	if (py == vy && abs(px - vx) < VISION_RANGE && abs(px - vx) > ATTACK_RANGE && (anim == STAND_L || anim == STAND_R || anim == ATTACK_L || anim == ATTACK_R))		//Walk to player
	{
		if (anim == STAND_L || anim == ATTACK_L)
			sprite->changeAnimation(WALK_L);
		else
			sprite->changeAnimation(WALK_R);
	}

	if ((anim == WALK_L || anim == WALK_R || anim == ATTACK_L || anim == ATTACK_R) && (py != vy || abs(px - vx) >= VISION_RANGE))		//Stand
	{
		if (anim == WALK_L || anim == ATTACK_L)
			sprite->changeAnimation(STAND_L);
		else
			sprite->changeAnimation(STAND_R);
	}

	if (py == vy && abs(px - vx) <= ATTACK_RANGE && (anim == STAND_L || anim == STAND_R || anim == WALK_L || anim == WALK_R))		//Attack player
	{
		if (anim == STAND_L || anim == WALK_L)
			sprite->changeAnimation(ATTACK_L);
		else
			sprite->changeAnimation(ATTACK_R);
	}

	if (health == 0 && anim != DIE_L && anim != DIE_R && anim != DEAD_L && anim != DEAD_R)									//Die
	{
		if (anim == STAND_L || anim == WALK_L || anim == ATTACK_L)
			sprite->changeAnimation(DIE_L);
		else
			sprite->changeAnimation(DIE_R);
	}

	if ((anim == DIE_L || anim == DIE_R) && sprite->animFinished())				//Dead
	{
		if (anim == DIE_L)
			sprite->changeAnimation(DEAD_L);
		else
			sprite->changeAnimation(DEAD_R);
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