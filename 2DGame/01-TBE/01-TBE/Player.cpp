#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, STANDLR, STANDRL,START_LEFT, START_RIGHT,MOVE_LEFT, MOVE_RIGHT, STOP_LEFT , STOP_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	bRunning = false;
	direction = "left";
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/kidrun.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(-0.1f, 0.f));

	sprite->setAnimationSpeed(STANDLR, 8);
	sprite->addKeyframe(STANDLR, glm::vec2(-0.6f, 0.05f));
	sprite->addKeyframe(STANDLR, glm::vec2(-0.7f, 0.05f));
	sprite->addKeyframe(STANDLR, glm::vec2(-0.8f, 0.05f));
	sprite->addKeyframe(STANDLR, glm::vec2(-0.9f, 0.05f));
	sprite->addKeyframe(STANDLR, glm::vec2(-1.f, 0.05f));
	sprite->addKeyframe(STANDLR, glm::vec2(-0.1f, 0.1f));
	sprite->addKeyframe(STANDLR, glm::vec2(-0.2f, 0.1f));
	sprite->addKeyframe(STANDLR, glm::vec2(-0.3f, 0.1f));

	sprite->setAnimationSpeed(STANDRL, 8);
	sprite->addKeyframe(STANDRL, glm::vec2(0.5f, 0.05f));
	sprite->addKeyframe(STANDRL, glm::vec2(0.6f, 0.05f));
	sprite->addKeyframe(STANDRL, glm::vec2(0.7f, 0.05f));
	sprite->addKeyframe(STANDRL, glm::vec2(0.8f, 0.05f));
	sprite->addKeyframe(STANDRL, glm::vec2(0.9f, 0.05f));
	sprite->addKeyframe(STANDRL, glm::vec2(0.f, 0.1f));
	sprite->addKeyframe(STANDRL, glm::vec2(0.1f, 0.1f));
	sprite->addKeyframe(STANDRL, glm::vec2(0.2f, 0.1f));

	sprite->setAnimationSpeed(START_LEFT, 8);
	sprite->addKeyframe(START_LEFT, glm::vec2(0.1f, 0.f));
	sprite->addKeyframe(START_LEFT, glm::vec2(0.2f, 0.f));
	sprite->addKeyframe(START_LEFT, glm::vec2(0.3f, 0.f));
	sprite->addKeyframe(START_LEFT, glm::vec2(0.4f, 0.f));

	sprite->setAnimationSpeed(START_RIGHT, 8);
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.2f, 0.f));
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.3f, 0.f));
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.4f, 0.f));
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.5f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.7f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.8f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.9f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.05f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.1f, 0.05f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f, 0.05f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.3f, 0.05f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.4f, 0.05f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-0.6f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-0.7f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-0.8f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-0.9f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-1.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-0.1f, 0.05f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-0.2f, 0.05f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-0.3f, 0.05f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-0.4f, 0.05f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(-0.5f, 0.05f));


	sprite->setAnimationSpeed(STOP_LEFT, 8);
	sprite->addKeyframe(STOP_LEFT, glm::vec2(0.3f, 0.1f));
	sprite->addKeyframe(STOP_LEFT, glm::vec2(0.4f, 0.1f));
	sprite->addKeyframe(STOP_LEFT, glm::vec2(0.5f, 0.1f));
	sprite->addKeyframe(STOP_LEFT, glm::vec2(0.6f, 0.1f));

	sprite->setAnimationSpeed(STOP_RIGHT, 8);
	sprite->addKeyframe(STOP_RIGHT, glm::vec2(-0.4f, 0.1f));
	sprite->addKeyframe(STOP_RIGHT, glm::vec2(-0.5f, 0.1f));
	sprite->addKeyframe(STOP_RIGHT, glm::vec2(-0.6f, 0.1f));
	sprite->addKeyframe(STOP_RIGHT, glm::vec2(-0.7f, 0.1f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x+posPlayer.x), float(tileMapDispl.y+posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	switch (sprite->animation()){
	case MOVE_LEFT:
		posPlayer.x -= 2;
		break;
	case MOVE_RIGHT:
		posPlayer.x += 2;
		break;
	case STOP_LEFT:
		posPlayer.x -= 2;
		break;
	case STOP_RIGHT:
		posPlayer.x += 2;
		break;
	case START_LEFT:
		posPlayer.x -= 2;
		break;
	case START_RIGHT:
		posPlayer.x += 2;
		break;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (direction != "left" && sprite->animFinished() && !bRunning){
			sprite->changeAnimation(STANDRL);
			direction = "left";
		}
		else if (sprite->animation() != MOVE_LEFT && sprite->animFinished() && !bRunning){ //abans sempre si no mira en la bona direcció es gira
			sprite->changeAnimation(START_LEFT);
			bRunning = true;
		}

		else if (sprite->animation() == START_LEFT && sprite->animFinished())
			sprite->changeAnimation(MOVE_LEFT);

		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 64)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (direction != "right" && sprite->animFinished() && !bRunning){
			sprite->changeAnimation(STANDLR);
			direction = "right";
		}
		else if (sprite->animation() != MOVE_RIGHT && sprite->animFinished() && !bRunning){
			sprite->changeAnimation(START_RIGHT);
			bRunning = true;
		}

		else if (sprite->animation() == START_RIGHT && sprite->animFinished())
			sprite->changeAnimation(MOVE_RIGHT);

			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 64)))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
	}
	else if (sprite->animFinished()) // ni left ni right apretat
	{
		if (sprite->animation() == STOP_LEFT ||  sprite->animation() == STANDRL)//substituir per not running
			sprite->changeAnimation(STAND_LEFT);
		if (sprite->animation() == STOP_RIGHT ||  sprite->animation() == STANDLR)
			sprite->changeAnimation(STAND_RIGHT);
		if (bRunning && direction == "left"){
			sprite->changeAnimation(STOP_LEFT);
			bRunning = false;
		}
		if (bRunning && direction == "right"){
			sprite->changeAnimation(STOP_RIGHT);
			bRunning = false;
		}
	}

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y))
		{
		/**	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}**/
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




