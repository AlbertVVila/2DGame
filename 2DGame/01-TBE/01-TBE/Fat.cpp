#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Fat.h"
#include "Game.h"

#define VISION_RANGE 32 * 5			//distancia en que pot veure al player
#define ATTACK_RANGE 32 * 1 + 12	//distancia en que pot atacar al player
#define COOLDOWN 1000				//temps per fer la seg�ent habilitat (attack o block)
#define CD_DAMAGE 500				//temps per rebre el seg�ent atac del player
#define CD_STAR	100					//temps que dura l'estrella

enum FatAnims
{
	STAND_L, STAND_R,
	WALK_L, WALK_R,
	ATTACK_L, ATTACK_R,
	BLOCK_L, BLOCK_R,
	CD_L, CD_R,
	DIE_L, DIE_R,
	DEAD_L, DEAD_R
};

enum StarAnims
{
	ON, OFF
};

enum LifeAnims
{
	FULL, HALFUP, HALFDOWN, NONE
};


void Fat::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/fat.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(14);

	lifesheet.setWrapS(GL_MIRRORED_REPEAT);
	lifesheet.loadFromFile("images/fat_life_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	life = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 1), &lifesheet, &shaderProgram);
	life->setNumberAnimations(4);

	star = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.25), &spritesheet, &shaderProgram);
	star->setNumberAnimations(2);


	star->setAnimationSpeed(ON, 8);
	star->addKeyframe(ON, glm::vec2(0.8f, 0.0f));

	star->setAnimationSpeed(OFF, 8);
	star->addKeyframe(OFF, glm::vec2(0.9f, 0.0f));

	life->setAnimationSpeed(FULL, 8);
	life->addKeyframe(FULL, glm::vec2(0.0f, 0.0f));

	life->setAnimationSpeed(HALFUP, 8);
	life->addKeyframe(HALFUP, glm::vec2(0.1f, 0.0f));

	life->setAnimationSpeed(HALFDOWN, 8);
	life->addKeyframe(HALFDOWN, glm::vec2(0.2f, 0.0f));

	life->setAnimationSpeed(NONE, 8);
	life->addKeyframe(NONE, glm::vec2(0.3f, 0.0f));

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
	star->changeAnimation(OFF);
	life->changeAnimation(FULL);
	frameant = 0;
	health = 3;
	cd_damage = 0;
	cd_star = 0;
	bloked = false;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFat.x), float(tileMapDispl.y + posFat.y)));
	star->setPosition(glm::vec2(float(tileMapDispl.x + posFat.x), float(tileMapDispl.y + posFat.y)));
	life->setPosition(glm::vec2(float(tileMapDispl.x + posFat.x), float(tileMapDispl.y + posFat.y)));
}

void Fat::update(int deltaTime)
{
	sprite->update(deltaTime);
	int frame = sprite->getFrame();
	int px = player->getPosition().x;
	int py = player->getPosition().y;
	int vx = posFat.x;
	int vy = posFat.y;
	int anim = sprite->animation();
	bool chase = py == vy && abs(px - vx) < VISION_RANGE && abs(px - vx) > ATTACK_RANGE;
	bool outsight = (py != vy || abs(px - vx) >= VISION_RANGE);
	bool attack = py == vy && abs(px - vx) <= ATTACK_RANGE;

	switch (anim)
	{
	case STAND_L:
		if (px > vx) sprite->changeAnimation(STAND_R);
		else if (chase) { player->setCombat(true); sprite->changeAnimation(WALK_L); }
		else if (attack) { player->setCombat(true); sprite->changeAnimation(ATTACK_L); }
		break;
	case STAND_R:
		if (px < vx) sprite->changeAnimation(STAND_L);
		else if (chase) { player->setCombat(true); sprite->changeAnimation(WALK_R); }
		else if (attack) { player->setCombat(true); sprite->changeAnimation(ATTACK_R); }
		break;
	case ATTACK_L:
		if (health == 0) sprite->changeAnimation(DIE_L);
		else if (px > vx) { sprite->changeAnimation(STAND_R); player->changeDirection(); }
		else if (chase) sprite->changeAnimation(STAND_L);
		else if (outsight) { player->setCombat(false); sprite->changeAnimation(STAND_L); }
		else if (sprite->animFinished()) { cd = 0; sprite->changeAnimation(CD_L); }
		else if (frameant == 1 && frame == 2) posFat.x -= 11;
		else if (frameant == 2 && frame == 3) posFat.x -= 4;
		else if (frameant == 3 && frame == 4) posFat.x += 13;
		else if (frameant == 4 && frame == 5) posFat.x += 2;
		if (frameant == 2 && frame == 3 && !player->isBlocking() && !player->isDead()) player->damage(1, "enemy");
		break;
	case ATTACK_R:
		if (health == 0) sprite->changeAnimation(DIE_R);
		else if (px < vx) { sprite->changeAnimation(STAND_L); player->changeDirection(); }
		else if (chase) sprite->changeAnimation(STAND_R);
		else if (outsight) { player->setCombat(false); sprite->changeAnimation(STAND_R); }
		else if (sprite->animFinished()) { cd = 0; sprite->changeAnimation(CD_R); }
		else if (frameant == 1 && frame == 2) posFat.x += 11;
		else if (frameant == 2 && frame == 3) posFat.x += 4;
		else if (frameant == 3 && frame == 4) posFat.x -= 13;
		else if (frameant == 4 && frame == 5) posFat.x -= 2;
		if (frameant == 2 && frame == 3 && !player->isBlocking() && !player->isDead()) player->damage(1, "enemy");
		break;
	case CD_L:
		cd += deltaTime;
		if (health == 0) sprite->changeAnimation(DIE_L);
		if (strike < 3) { strike += 1; sprite->changeAnimation(ATTACK_L); }
		else if (cd >= COOLDOWN && player->isAttackingLong() && !bloked) { bloked = true;  sprite->changeAnimation(BLOCK_L); }
		else if (cd >= COOLDOWN) { bloked = false; strike = 0; cd = 0; sprite->changeAnimation(CD_L); }
		break;
	case CD_R:
		cd += deltaTime;
		if (health == 0) sprite->changeAnimation(DIE_R);
		if (strike < 3) { strike += 1; sprite->changeAnimation(ATTACK_R); }
		else if (cd >= COOLDOWN && player->isAttackingLong() && !bloked) { bloked = true;  sprite->changeAnimation(BLOCK_R); }
		else if (cd >= COOLDOWN) { bloked = false;  strike = 0; cd = 0; sprite->changeAnimation(CD_R); }
		break;
	case WALK_L:
		if (frameant == 0 && frame == 1) posFat.x -= 12;
		if (health == 0) sprite->changeAnimation(DIE_L);
		else if (outsight) { player->setCombat(false); sprite->changeAnimation(STAND_L); }
		else if (attack) { cd = 0; strike = 0; sprite->changeAnimation(CD_L); }
		break;
	case WALK_R:
		if (frameant == 0 && frame == 1) posFat.x += 12;
		if (health == 0) sprite->changeAnimation(DIE_R);
		else if (outsight) { player->setCombat(false); sprite->changeAnimation(STAND_R); }
		else if (attack) { cd = 0; strike = 0; sprite->changeAnimation(CD_R); }
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

	if (player->isAttacking() && cd_damage >= CD_DAMAGE && anim != BLOCK_L && anim != BLOCK_R  && anim != DEAD_L && anim != DEAD_R && attack)
	{
		cd_damage = 0;
		health -= 1;
		if (life->animation() == FULL) life->changeAnimation(HALFUP);
		else if (life->animation() == HALFUP) life->changeAnimation(HALFDOWN);
		else if (life->animation() == HALFDOWN) life->changeAnimation(NONE);
		star->changeAnimation(ON);
		cd_star = 0;
		//cd = -COOLDOWN;
		//if (anim == ATTACK_L || anim == CD_L || anim == BLOCK_L) sprite->changeAnimation(CD_L);
		//if (anim == ATTACK_R || anim == CD_R || anim == BLOCK_R) sprite->changeAnimation(CD_R);
	}
	else cd_damage += deltaTime;
	if (star->animation() == ON) cd_star += deltaTime;
	if (star->animation() == ON && cd_star >= CD_STAR) star->changeAnimation(OFF);

	frameant = frame;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFat.x), float(tileMapDispl.y + posFat.y)));
	star->setPosition(glm::vec2(float(tileMapDispl.x + posFat.x), float(tileMapDispl.y + posFat.y)));
	life->setPosition(glm::vec2(float(tileMapDispl.x + posFat.x), float(tileMapDispl.y + posFat.y)));
}

void Fat::render()
{
	sprite->render();
	star->render();
	life->render();
}

void Fat::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Fat::setPlayer(Player *p)
{
	player = p;
}

void Fat::setPosition(const glm::vec2 &pos)
{
	posFat = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFat.x), float(tileMapDispl.y + posFat.y)));
	star->setPosition(glm::vec2(float(tileMapDispl.x + posFat.x), float(tileMapDispl.y + posFat.y)));
	life->setPosition(glm::vec2(float(tileMapDispl.x + posFat.x), float(tileMapDispl.y + posFat.y)));
}