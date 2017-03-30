#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Vizier.h"
#include "Game.h"

#define TIME_A 2000
#define VISION_RANGE 32 * 5
#define ATTACK_RANGE 32 * 1 + 12
#define COOLDOWN 500
#define CD_DAMAGE 500

enum VizierAnims
{
	STAND_L, STAND_R,
	WALK_L, WALK_R,
	ATTACK_L, ATTACK_R,
	BLOCK_L, BLOCK_R,
	CD_L, CD_R,
	DIE_L, DIE_R,
	DEAD_L, DEAD_R
};


void Vizier::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/vizier.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(14);

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

	sprite->setAnimationSpeed(BLOCK_L, 8);
	sprite->addKeyframe(BLOCK_L, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(BLOCK_L, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(BLOCK_L, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(BLOCK_L, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(BLOCK_L, glm::vec2(0.0f, 0.5f));

	sprite->setAnimationSpeed(BLOCK_R, 8);
	sprite->addKeyframe(BLOCK_R, glm::vec2(-0.1f, 0.5f));
	sprite->addKeyframe(BLOCK_R, glm::vec2(-0.1f, 0.5f));
	sprite->addKeyframe(BLOCK_R, glm::vec2(-0.1f, 0.5f));
	sprite->addKeyframe(BLOCK_R, glm::vec2(-0.1f, 0.5f));
	sprite->addKeyframe(BLOCK_R, glm::vec2(-0.1f, 0.5f));

	sprite->setAnimationSpeed(CD_L, 8);
	sprite->addKeyframe(CD_L, glm::vec2(0.6f, 0.25f));

	sprite->setAnimationSpeed(CD_R, 8);
	sprite->addKeyframe(CD_R, glm::vec2(-0.7f, 0.25f));

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
	frameant = 0;
	health = 3;
	cd_damage = 0;
	bloked = false;
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
	bool chase = py == vy && abs(px - vx) < VISION_RANGE && abs(px - vx) > ATTACK_RANGE;
	bool outsight = (py != vy || abs(px - vx) >= VISION_RANGE);
	bool attack = py == vy && abs(px - vx) <= ATTACK_RANGE;
	bool block = false;

	switch (anim)
	{
	case STAND_L:
		if (health == 0) sprite->changeAnimation(DIE_L);
		else if (px > vx) sprite->changeAnimation(STAND_R);
		else if (chase) { player->setCombat(true); sprite->changeAnimation(WALK_L); }
		else if (attack) { player->setCombat(true); sprite->changeAnimation(ATTACK_L); }
		break;
	case STAND_R:
		if (health == 0) sprite->changeAnimation(DIE_R);
		else if (px < vx) sprite->changeAnimation(STAND_L);
		else if (chase) { player->setCombat(true); sprite->changeAnimation(WALK_R); }
		else if (attack) { player->setCombat(true); sprite->changeAnimation(ATTACK_R); }
		break;
	case ATTACK_L:
		if (health == 0) sprite->changeAnimation(DIE_L);
		else if (px > vx) sprite->changeAnimation(STAND_R);
		else if (chase && sprite->animFinished()) sprite->changeAnimation(WALK_L);
		else if (outsight) { player->setCombat(false); sprite->changeAnimation(STAND_L); }
		else if (sprite->animFinished()) { cd = 0; sprite->changeAnimation(CD_L); }
		else if (frameant == 1 && frame == 2) posVizier.x -= 11;
		else if (frameant == 2 && frame == 3) posVizier.x -= 4;
		else if (frameant == 3 && frame == 4) posVizier.x += 13;
		else if (frameant == 4 && frame == 5) posVizier.x += 2;
		if (frame == 3 && !player->isBlocking() && !player->isDead()) player->damage(1,"enemy");
		break;
	case ATTACK_R:
		if (health == 0) sprite->changeAnimation(DIE_R);
		else if (px < vx) sprite->changeAnimation(STAND_L);
		else if (chase && sprite->animFinished()) sprite->changeAnimation(WALK_R);
		else if (outsight) { player->setCombat(false); sprite->changeAnimation(STAND_R); }
		else if (sprite->animFinished()) { cd = 0; sprite->changeAnimation(CD_R); }
		else if (frameant == 1 && frame == 2) posVizier.x += 11;
		else if (frameant == 2 && frame == 3) posVizier.x += 4;
		else if (frameant == 3 && frame == 4) posVizier.x -= 13;
		else if (frameant == 4 && frame == 5) posVizier.x -= 2;
		if (frame == 3 && !player->isBlocking() && !player->isDead()) player->damage(1, "enemy");
		break;
	case CD_L:
		cd += deltaTime;
		if (health == 0) sprite->changeAnimation(DIE_L);
		else if (cd >= COOLDOWN && player->isAttackingLong() && !bloked) { bloked = true;  sprite->changeAnimation(BLOCK_L); }
		else if (cd >= COOLDOWN) { bloked = false; sprite->changeAnimation(ATTACK_L); }
		break;
	case CD_R:
		cd += deltaTime;
		if (health == 0) sprite->changeAnimation(DIE_R);
		else if (cd >= COOLDOWN && player->isAttackingLong() && !bloked) { bloked = true;  sprite->changeAnimation(BLOCK_R); }
		else if (cd >= COOLDOWN) { bloked = false; sprite->changeAnimation(ATTACK_R); }
		break;
	case WALK_L:
		if (frameant == 0 && frame == 1) posVizier.x -= 12;
		if (health == 0) sprite->changeAnimation(DIE_L);
		else if (outsight) { player->setCombat(false); sprite->changeAnimation(STAND_L); }
		else if (attack) { cd = 0; sprite->changeAnimation(CD_L); }
		break;
	case WALK_R:
		if (frameant == 0 && frame == 1) posVizier.x += 12;
		if (health == 0) sprite->changeAnimation(DIE_R);
		else if (outsight) { player->setCombat(false); sprite->changeAnimation(STAND_R); }
		else if (attack) { cd = 0; sprite->changeAnimation(CD_R); }
		break;
	case BLOCK_L:
		if (health == 0) sprite->changeAnimation(DIE_L);
		else if (sprite->animFinished()) { cd = 0; sprite->changeAnimation(CD_L); }
		break;
	case BLOCK_R:
		if (health == 0) sprite->changeAnimation(DIE_R);
		else if (sprite->animFinished()) { cd = 0; sprite->changeAnimation(CD_R); }
		break;
	case DIE_L:
		if (sprite->animFinished()) { player->setCombat(false); sprite->changeAnimation(DEAD_L); }
		break;
	case DIE_R:
		if (sprite->animFinished()) { player->setCombat(false); sprite->changeAnimation(DEAD_R); }
		break;
	}

	if (player->isAttacking() && cd_damage >= CD_DAMAGE && anim!=BLOCK_L && anim!=BLOCK_R && attack)
	{
		cd_damage = 0;
		health -= 1;
		//cd = -COOLDOWN;
		//if (anim == ATTACK_L || anim == CD_L || anim == BLOCK_L) sprite->changeAnimation(CD_L);
		//if (anim == ATTACK_R || anim == CD_R || anim == BLOCK_R) sprite->changeAnimation(CD_R);
	}
	else cd_damage += deltaTime;

	frameant = frame;
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