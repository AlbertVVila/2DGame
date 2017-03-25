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
	SJUMP_LEFT_START, SJUMP_RIGHT_START, SJUMP_LEFT_END, SJUMP_RIGHT_END, RJUMP_LEFT_START, RJUMP_RIGHT_START, RJUMP_LEFT_END, RJUMP_RIGHT_END, 
	FALL_LEFT, FALL_RIGHT, FALLING_LEFT, FALLING_RIGHT, STAND_UP_LEFT, STAND_UP_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	bRunning = false;
	bFalling = false;
	direction = "left";
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/kidrun.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(34);

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

	sprite->setAnimationSpeed(JUMP_LEFT, 10);
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

	sprite->setAnimationSpeed(JUMP_RIGHT, 10);
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
	//sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.3f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.4f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.6f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_FAIL, glm::vec2(0.7f, 0.25f));

	sprite->setAnimationSpeed(JUMP_RIGHT_FAIL, 8);
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.3f, 0.25f));
	//sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.4f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.5f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.6f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.7f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_FAIL, glm::vec2(-0.8f, 0.25f));
	
	sprite->setAnimationSpeed(JUMP_LEFT_CATCH, 4);
	sprite->addKeyframe(JUMP_LEFT_CATCH, glm::vec2(0.8f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_CATCH, glm::vec2(0.8f, 0.25f));

	sprite->setAnimationSpeed(JUMP_RIGHT_CATCH, 1);
	sprite->addKeyframe(JUMP_RIGHT_CATCH, glm::vec2(-0.9f, 0.25f));

	sprite->setAnimationSpeed(JUMP_LEFT_SUCCESS, 8);
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.9f, 0.25f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.1f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.2f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.3f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.4f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.5f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.6f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.7f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.8f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.9f, 0.3f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.f, 0.35f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.1f, 0.35f));
	sprite->addKeyframe(JUMP_LEFT_SUCCESS, glm::vec2(0.2f, 0.35f));

	sprite->setAnimationSpeed(JUMP_RIGHT_SUCCESS, 8);
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-1.f, 0.25f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.1f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.2f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.3f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.4f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.5f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.6f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.7f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.8f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.9f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-1.f, 0.3f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.1f, 0.35f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.2f, 0.35f));
	sprite->addKeyframe(JUMP_RIGHT_SUCCESS, glm::vec2(-0.3f, 0.35f));
	
	sprite->setAnimationSpeed(FALL_LEFT, 8);
	sprite->addKeyframe(FALL_LEFT, glm::vec2(0.3f, 0.35f));
	sprite->addKeyframe(FALL_LEFT, glm::vec2(0.4f, 0.35f));
	sprite->addKeyframe(FALL_LEFT, glm::vec2(0.5f, 0.35f));
	sprite->addKeyframe(FALL_LEFT, glm::vec2(0.6f, 0.35f));
	

	sprite->setAnimationSpeed(FALL_RIGHT,8);
	sprite->addKeyframe(FALL_RIGHT, glm::vec2(-0.4f, 0.35f));
	sprite->addKeyframe(FALL_RIGHT, glm::vec2(-0.5f, 0.35f));
	sprite->addKeyframe(FALL_RIGHT, glm::vec2(-0.6f, 0.35f));
	sprite->addKeyframe(FALL_RIGHT, glm::vec2(-0.7f, 0.35f));

	
	sprite->setAnimationSpeed(FALLING_LEFT, 8);
	sprite->addKeyframe(FALLING_LEFT, glm::vec2(0.7f, 0.35f));

	sprite->setAnimationSpeed(FALLING_RIGHT, 8);
	sprite->addKeyframe(FALLING_RIGHT, glm::vec2(-0.8f, 0.35f));

	sprite->setAnimationSpeed(STAND_UP_LEFT, 8);
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.8f, 0.35f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.9f, 0.35f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.1f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.2f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.3f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.4f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.5f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.6f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.7f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.8f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.9f, 0.4f));
	sprite->addKeyframe(STAND_UP_LEFT, glm::vec2(0.f, 0.45f));

	sprite->setAnimationSpeed(STAND_UP_RIGHT, 8);
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.9f, 0.35f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-1.f, 0.35f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.1f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.2f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.3f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.4f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.5f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.6f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.7f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.8f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.9f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-1.f, 0.4f));
	sprite->addKeyframe(STAND_UP_RIGHT, glm::vec2(-0.1f, 0.45f));

	sprite->setAnimationSpeed(SJUMP_LEFT_START, 8);
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.1f, 0.45f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.2f, 0.45f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.3f, 0.45f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.4f, 0.45f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.5f, 0.45f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.6f, 0.45f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.7f, 0.45f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.8f, 0.45f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.9f, 0.45f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(SJUMP_LEFT_START, glm::vec2(0.1f, 0.5f));

	sprite->setAnimationSpeed(SJUMP_RIGHT_START, 8);
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.2f, 0.45f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.3f, 0.45f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.4f, 0.45f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.5f, 0.45f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.6f, 0.45f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.7f, 0.45f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.8f, 0.45f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.9f, 0.45f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-1.f, 0.45f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.1f, 0.5f));
	sprite->addKeyframe(SJUMP_RIGHT_START, glm::vec2(-0.2f, 0.5f));

	sprite->setAnimationSpeed(SJUMP_LEFT_END, 8);
	sprite->addKeyframe(SJUMP_LEFT_END, glm::vec2(0.2f, 0.5f));
	sprite->addKeyframe(SJUMP_LEFT_END, glm::vec2(0.3f, 0.5f));
	sprite->addKeyframe(SJUMP_LEFT_END, glm::vec2(0.4f, 0.5f));
	sprite->addKeyframe(SJUMP_LEFT_END, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(SJUMP_LEFT_END, glm::vec2(0.6f, 0.5f));
	sprite->addKeyframe(SJUMP_LEFT_END, glm::vec2(0.7f, 0.5f));
	sprite->addKeyframe(SJUMP_LEFT_END, glm::vec2(0.8f, 0.5f));

	sprite->setAnimationSpeed(SJUMP_RIGHT_END, 8);
	sprite->addKeyframe(SJUMP_RIGHT_END, glm::vec2(-0.3f, 0.5f));
	sprite->addKeyframe(SJUMP_RIGHT_END, glm::vec2(-0.4f, 0.5f));
	sprite->addKeyframe(SJUMP_RIGHT_END, glm::vec2(-0.5f, 0.5f));
	sprite->addKeyframe(SJUMP_RIGHT_END, glm::vec2(-0.6f, 0.5f));
	sprite->addKeyframe(SJUMP_RIGHT_END, glm::vec2(-0.7f, 0.5f));
	sprite->addKeyframe(SJUMP_RIGHT_END, glm::vec2(-0.8f, 0.5f));
	sprite->addKeyframe(SJUMP_RIGHT_END, glm::vec2(-0.9f, 0.5f));

	sprite->setAnimationSpeed(RJUMP_LEFT_START, 8);
	sprite->addKeyframe(RJUMP_LEFT_START, glm::vec2(0.9f, 0.5f));
	sprite->addKeyframe(RJUMP_LEFT_START, glm::vec2(0.f, 0.55f));
	sprite->addKeyframe(RJUMP_LEFT_START, glm::vec2(0.1f, 0.55f));
	sprite->addKeyframe(RJUMP_LEFT_START, glm::vec2(0.2f, 0.55f));
	sprite->addKeyframe(RJUMP_LEFT_START, glm::vec2(0.3f, 0.55f));
	sprite->addKeyframe(RJUMP_LEFT_START, glm::vec2(0.4f, 0.55f));
	sprite->addKeyframe(RJUMP_LEFT_START, glm::vec2(0.5f, 0.55f));
	sprite->addKeyframe(RJUMP_LEFT_START, glm::vec2(0.6f, 0.55f));
	sprite->addKeyframe(RJUMP_LEFT_START, glm::vec2(0.7f, 0.55f));

	sprite->setAnimationSpeed(RJUMP_RIGHT_START, 8);
	sprite->addKeyframe(RJUMP_RIGHT_START, glm::vec2(-1.f, 0.5f));
	sprite->addKeyframe(RJUMP_RIGHT_START, glm::vec2(-0.1f, 0.55f));
	sprite->addKeyframe(RJUMP_RIGHT_START, glm::vec2(-0.2f, 0.55f));
	sprite->addKeyframe(RJUMP_RIGHT_START, glm::vec2(-0.3f, 0.55f));
	sprite->addKeyframe(RJUMP_RIGHT_START, glm::vec2(-0.4f, 0.55f));
	sprite->addKeyframe(RJUMP_RIGHT_START, glm::vec2(-0.5f, 0.55f));
	sprite->addKeyframe(RJUMP_RIGHT_START, glm::vec2(-0.6f, 0.55f));
	sprite->addKeyframe(RJUMP_RIGHT_START, glm::vec2(-0.7f, 0.55f));
	sprite->addKeyframe(RJUMP_RIGHT_START, glm::vec2(-0.8f, 0.55f));

	sprite->setAnimationSpeed(RJUMP_LEFT_END, 8);
	sprite->addKeyframe(RJUMP_LEFT_END, glm::vec2(0.8f, 0.55f));
	sprite->addKeyframe(RJUMP_LEFT_END, glm::vec2(0.9f, 0.55f));

	sprite->setAnimationSpeed(RJUMP_RIGHT_END, 8);
	sprite->addKeyframe(RJUMP_RIGHT_END, glm::vec2(-0.9f, 0.55f));
	sprite->addKeyframe(RJUMP_RIGHT_END, glm::vec2(-1.f, 0.55f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x+posPlayer.x), float(tileMapDispl.y+posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	int frame = sprite->getFrame();
	switch (sprite->animation()){
	case STAND_LEFT:
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(112) && !map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(SLOW_LEFT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(START_LEFT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(STANDLR);
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(JUMP_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_LEFT);
		break;

	case STAND_RIGHT:
		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(112) && !map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(SLOW_RIGHT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP) && Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(SJUMP_RIGHT_START);
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(START_RIGHT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) sprite->changeAnimation(STANDRL); 
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(JUMP_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_RIGHT);
		break;

	case STANDRL:
		if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		break;

	case STANDLR:
		if (sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		break;

	case START_LEFT:
		if (frame==0 && Game::instance().getSpecialKey(GLUT_KEY_UP) && Game::instance().getSpecialKey(GLUT_KEY_LEFT)) sprite->changeAnimation(SJUMP_LEFT_START);
		if (frame >= 4)posPlayer.x -= 1;
		if (sprite->animFinished() &&  Game::instance().getSpecialKey(GLUT_KEY_LEFT)) sprite->changeAnimation(MOVE_LEFT); //aqui podriem mirar si volem fer transició directa a slow
		else if (sprite->animFinished()) sprite->changeAnimation(STOP_LEFT);

		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_LEFT);
		break;

	case START_RIGHT:
		if (frame == 0 && Game::instance().getSpecialKey(GLUT_KEY_UP) && Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(SJUMP_RIGHT_START);
		if (frame >= 4)posPlayer.x += 1;
		if (sprite->animFinished() && Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(MOVE_RIGHT);
		else if (sprite->animFinished()) sprite->changeAnimation(STOP_RIGHT);

		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_RIGHT);
		break;

	case MOVE_LEFT:
		posPlayer.x -= 1;
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(RJUMP_LEFT_START);
		if (sprite->animFinished() && !Game::instance().getSpecialKey(GLUT_KEY_LEFT)) sprite->changeAnimation(STOP_LEFT);
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_LEFT);

		break;

	case MOVE_RIGHT:
		posPlayer.x += 1;
		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(RJUMP_RIGHT_START);
		if (sprite->animFinished() && !Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(STOP_RIGHT);
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_RIGHT);
		break;

	case STOP_LEFT:
		posPlayer.x -= 1;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_LEFT);
		break;

	case STOP_RIGHT:
		posPlayer.x += 1;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_RIGHT);
		break;

	case SLOW_LEFT:
		if (frame > 2 && frame <5)posPlayer.x -= 1;
		else if (frame >= 8 && frame <= 10) posPlayer.x -= 1;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_LEFT);
		break;

	case SLOW_RIGHT:
		if (frame >2 && frame<5)posPlayer.x += 1;
		else if (frame >= 8 && frame <= 10) posPlayer.x += 1;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_RIGHT);
		break;

	case JUMP_LEFT:
		if (frame == 0 && Game::instance().getSpecialKey(GLUT_KEY_UP) && Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(SJUMP_LEFT_START);
		if (frame>9) posPlayer.y--;
		if(sprite->animFinished()){
			if (map->JumpableLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(JUMP_LEFT_CATCH);
			else sprite->changeAnimation(JUMP_LEFT_FAIL);
		}
		break;

	case JUMP_RIGHT:
		if (frame == 0 && Game::instance().getSpecialKey(GLUT_KEY_UP) && Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(SJUMP_RIGHT_START);
		if (frame>9) posPlayer.y--;
		if (sprite->animFinished()){
			if (map->JumpableRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(JUMP_RIGHT_CATCH);
			else sprite->changeAnimation(JUMP_RIGHT_FAIL);
		}
		break;

	case JUMP_LEFT_CATCH:
		if (sprite->animFinished() && Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(JUMP_LEFT_SUCCESS);
		else if (sprite->animFinished()) sprite->changeAnimation(JUMP_LEFT_FAIL);
		break;

	case JUMP_RIGHT_CATCH:
		if (sprite->animFinished() && Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(JUMP_RIGHT_SUCCESS);
		else if (sprite->animFinished()) sprite->changeAnimation(JUMP_RIGHT_FAIL);
		break;

	case JUMP_LEFT_FAIL:
		if (frame < 2) posPlayer.y++;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		break;

	case JUMP_RIGHT_FAIL:
		if (frame < 2) posPlayer.y++;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		break;

	case JUMP_LEFT_SUCCESS:
		if (frame < 7) posPlayer.y--;
		if (sprite->animFinished())sprite->changeAnimation(STAND_LEFT);
		break;

	case JUMP_RIGHT_SUCCESS:
		if (frame < 7) posPlayer.y--;
		if (sprite->animFinished())sprite->changeAnimation(STAND_RIGHT);
		break;

	case FALL_LEFT:
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(STAND_UP_LEFT);
		else if (sprite->animFinished()) sprite->changeAnimation(FALLING_LEFT);
		break;

	case FALL_RIGHT:
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(STAND_UP_RIGHT);
		else if (sprite->animFinished()) sprite->changeAnimation(FALLING_RIGHT);
		break;

	case FALLING_LEFT:
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(STAND_UP_LEFT);
		break;

	case FALLING_RIGHT:
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(STAND_UP_RIGHT);
		break;

	case STAND_UP_LEFT:
		if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		break;

	case STAND_UP_RIGHT:
		if (sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		break;

	case SJUMP_LEFT_START:
		if (frame >= 7) posPlayer.x -= 3;
		if (sprite->animFinished()){
			if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(SJUMP_LEFT_END);
			else sprite->changeAnimation(FALL_LEFT);
		}
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		break;

	case SJUMP_RIGHT_START:
		if (frame >= 7) posPlayer.x += 3;
		if (sprite->animFinished()){
			if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(SJUMP_RIGHT_END);
			else sprite->changeAnimation(FALL_RIGHT);
		}
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		break;

	case SJUMP_LEFT_END:
		if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		break;

	case SJUMP_RIGHT_END:
		if (sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		break;
		
	case RJUMP_LEFT_START:
		if (frame <= 4) {
			posPlayer.x -= 1;
			if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_LEFT);
		}
		else posPlayer.x -= 3;
		if (sprite->animFinished()){
			if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(RJUMP_LEFT_END);
			else sprite->changeAnimation(FALL_LEFT);
		}
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		break;

	case RJUMP_RIGHT_START:
		if (frame <= 4) {
			posPlayer.x += 1;
			if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(FALL_RIGHT);
		}
		else posPlayer.x += 3;
		if (sprite->animFinished()){
			if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(RJUMP_RIGHT_END);
			else sprite->changeAnimation(FALL_RIGHT);
		}
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		break;
	case RJUMP_LEFT_END:
		if (sprite->animFinished()) sprite->changeAnimation(MOVE_LEFT);
		break;
	case RJUMP_RIGHT_END:
		if (sprite->animFinished()) sprite->changeAnimation(MOVE_RIGHT);
		break;
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




