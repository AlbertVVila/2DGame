#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 1
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, STANDLR, STANDRL,SLOW_LEFT,SLOW_RIGHT,START_LEFT, START_RIGHT,MOVE_LEFT, MOVE_RIGHT, STOP_LEFT , STOP_RIGHT, 
	JUMP_LEFT, JUMP_RIGHT,JUMP_LEFT_FAIL, JUMP_RIGHT_FAIL, JUMP_LEFT_CATCH, JUMP_RIGHT_CATCH, JUMP_LEFT_SUCCESS, JUMP_RIGHT_SUCCESS,
	SJUMP_LEFT,SJUMP_RIGHT,RJUMP_LEFT,RJUMP_RIGHT,FALL_LEFT,FALL_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	bRunning = false;
	direction = "left";
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/kidrun.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(26);

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

	sprite->setAnimationSpeed(SLOW_LEFT, 16);
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.7f, 0.1f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.8f, 0.1f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.9f, 0.1f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.f, 0.15f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.1f, 0.15f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.2f, 0.15f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.3f, 0.15f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.4f, 0.15f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.5f, 0.15f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.6f, 0.15f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.7f, 0.15f));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0.8f, 0.15f));

	sprite->setAnimationSpeed(SLOW_RIGHT, 16);
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.8f, 0.1f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.9f, 0.1f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-1.f, 0.1f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.1f, 0.15f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.2f, 0.15f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.3f, 0.15f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.4f, 0.15f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.5f, 0.15f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.6f, 0.15f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.7f, 0.15f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.8f, 0.15f));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(-0.9f, 0.15f));

	sprite->setAnimationSpeed(START_LEFT, 8);
	sprite->addKeyframe(START_LEFT, glm::vec2(0.1f, 0.f));
	sprite->addKeyframe(START_LEFT, glm::vec2(0.2f, 0.f));
	sprite->addKeyframe(START_LEFT, glm::vec2(0.3f, 0.f));
	sprite->addKeyframe(START_LEFT, glm::vec2(0.4f, 0.f));
	sprite->addKeyframe(START_LEFT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(START_LEFT, glm::vec2(0.6f, 0.f));

	sprite->setAnimationSpeed(START_RIGHT, 8);
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.2f, 0.f));
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.3f, 0.f));
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.4f, 0.f));
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.5f, 0.f));
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.6f, 0.f));
	sprite->addKeyframe(START_RIGHT, glm::vec2(-0.7f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 12);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.7f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.8f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.9f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.05f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.1f, 0.05f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f, 0.05f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.3f, 0.05f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.4f, 0.05f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 12);
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

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.9f, 0.15f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.1f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.2f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.3f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.4f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.5f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.6f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.7f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.8f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.9f, 0.2f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.1f, 0.25f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-1.f, 0.15f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.1f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.2f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.3f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.4f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.5f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.6f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.7f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.8f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.9f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-1.f, 0.2f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.1f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(-0.2f, 0.25f));

	sprite->setAnimationSpeed(JUMP_LEFT_FAIL, 8);
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.2f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.3f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.4f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.6f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.7f, 0.25f));

	sprite->setAnimationSpeed(JUMP_RIGHT_FAIL, 8);
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.3f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.4f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.5f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.6f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.7f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.8f, 0.25f));
	
	
	//aquí ficaré el jump_fail que es en el cas que no faci el salt i falli i després hi haurà jump_catch i jump_succeed
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x+posPlayer.x), float(tileMapDispl.y+posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	int frame = sprite->getFrame();
	switch (sprite->animation()){
	case MOVE_LEFT:
		posPlayer.x -= 1;
		break;
	case MOVE_RIGHT:
		posPlayer.x += 1;
		break;
	case STOP_LEFT:
		posPlayer.x -= 1;
		break;
	case STOP_RIGHT:
		posPlayer.x += 1;
		break;
	case START_LEFT:
		if (frame>=4)posPlayer.x -= 1;
		break;
	case START_RIGHT:
		if (frame>=4)posPlayer.x += 1;
		break;
	case SLOW_LEFT:
		if (frame > 2 && frame <5)posPlayer.x -= 1;
		else if (frame >= 8 && frame <= 10) posPlayer.x -= 1;
		break;
	case SLOW_RIGHT:
		if (frame >2 && frame<5)posPlayer.x += 1;
		else if (frame >= 8 && frame <= 10) posPlayer.x += 1;
		break;
	case JUMP_LEFT:
	case JUMP_RIGHT:
		if (frame>9)posPlayer.y--;
		break;
	case JUMP_LEFT_FAIL:
	case JUMP_RIGHT_FAIL:
		if(frame<2)posPlayer.y++;
		break;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(112)){ //SHIFT
		if (sprite->animFinished() && direction == "left")
			sprite->changeAnimation(SLOW_LEFT);
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(112)){ //SHIFT
		if (sprite->animFinished() && direction == "right")
			sprite->changeAnimation(SLOW_RIGHT);
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

	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)){
		if (sprite->animFinished() && !bRunning && direction=="left"){ 
			sprite->changeAnimation(JUMP_LEFT);
			bJumping = true;
		}
		else if (sprite->animFinished() && !bRunning && direction == "right"){ 
			sprite->changeAnimation(JUMP_RIGHT);
			bJumping = true;
		}
	}
	else if (sprite->animFinished() && !bJumping) // ni left ni right apretat
	{
		if (!bRunning && direction == "left")
			sprite->changeAnimation(STAND_LEFT);
		if (!bRunning && direction == "right")
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
	
	if (bJumping && sprite->animFinished())
	{
		if (sprite->animation() == JUMP_LEFT){
			sprite->changeAnimation(JUMP_LEFT_FAIL);
		}
		else{
			bJumping = false;
		}
		/**jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 50 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y);
		}**/
	}
	else if (!bJumping)
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)) // hauria de ser 64x64
		{
			/**if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				sprite->changeAnimation(JUMP_LEFT);
				jumpAngle = 0;
				startY = posPlayer.y;
			}**/
		}
	}
	if (sprite->animation() != STAND_LEFT && direction == "left" && map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64)))
	{
		bRunning = false;
		sprite->changeAnimation(STAND_LEFT);
	}

	if (sprite->animation() != STAND_RIGHT && direction == "right" && map->collisionMoveRight(posPlayer, glm::ivec2(64, 64)))
	{
		bRunning = false;
		sprite->changeAnimation(STAND_RIGHT);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

glm::vec2 Player::getPosition()
{
	return posPlayer;
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




