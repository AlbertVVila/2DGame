#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 1
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define MAX_LIFE 4
#define CD_STAR	100	


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, STANDLR, STANDRL,SLOW_LEFT,SLOW_RIGHT,START_LEFT, START_RIGHT,MOVE_LEFT, MOVE_RIGHT, STOP_LEFT , STOP_RIGHT, 
	JUMP_LEFT, JUMP_RIGHT,JUMP_LEFT_FAIL, JUMP_RIGHT_FAIL, JUMP_LEFT_CATCH, JUMP_RIGHT_CATCH, JUMP_LEFT_SUCCESS, JUMP_RIGHT_SUCCESS,
	SJUMP_LEFT_START, SJUMP_RIGHT_START, SJUMP_LEFT_END, SJUMP_RIGHT_END, RJUMP_LEFT_START, RJUMP_RIGHT_START, RJUMP_LEFT_END, RJUMP_RIGHT_END, 
	FALL_LEFT, FALL_RIGHT, FALLING_LEFT, FALLING_RIGHT, STAND_UP_LEFT, STAND_UP_RIGHT,
	DESENFUNDA_LEFT, DESENFUNDA_RIGHT, ENFUNDA_LEFT, ENFUNDA_RIGHT, ATTACK_LEFT, ATTACK_RIGHT, BLOCK_LEFT, BLOCK_RIGHT, ENGARDE_LEFT, ENGARDE_RIGHT,
	AMOVE_LEFT_FORWARD, AMOVE_LEFT_BACK, AMOVE_RIGHT_FORWARD, AMOVE_RIGHT_BACK, DEATHPINX_LEFT, DEATHPINX_RIGHT, DEATHENEMY_LEFT, DEATHENEMY_RIGHT,
	DEATHFALL_LEFT,DEATHFALL_RIGHT
};

enum StarAnims
{
	ON, OFF
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bCombat = false;
	hp = 3;
	dead = false;
	falldist = 0;
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/kidrun.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.05), &spritesheet, &shaderProgram);
	star = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(54);
	star->setNumberAnimations(2);

	star->setAnimationSpeed(ON, 8);
	star->addKeyframe(ON, glm::vec2(0.9f, 0.8f));

	star->setAnimationSpeed(OFF, 8);
	star->addKeyframe(OFF, glm::vec2(0.9f, 0.85f));

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

	sprite->setAnimationSpeed(ENGARDE_LEFT, 8);
	sprite->addKeyframe(ENGARDE_LEFT, glm::vec2(0.f, 0.6f));

	sprite->setAnimationSpeed(ENGARDE_RIGHT, 8);
	sprite->addKeyframe(ENGARDE_RIGHT, glm::vec2(-0.1f, 0.6f));

	sprite->setAnimationSpeed(BLOCK_LEFT, 8);
	sprite->addKeyframe(BLOCK_LEFT, glm::vec2(0.1f, 0.6f));
	sprite->addKeyframe(BLOCK_LEFT, glm::vec2(0.1f, 0.6f));
	sprite->addKeyframe(BLOCK_LEFT, glm::vec2(0.1f, 0.6f));


	sprite->setAnimationSpeed(BLOCK_RIGHT, 8);
	sprite->addKeyframe(BLOCK_RIGHT, glm::vec2(-0.2f, 0.6f));
	sprite->addKeyframe(BLOCK_RIGHT, glm::vec2(-0.2f, 0.6f));
	sprite->addKeyframe(BLOCK_RIGHT, glm::vec2(-0.2f, 0.6f)); //Falta anim res592

	sprite->setAnimationSpeed(DESENFUNDA_LEFT, 8);
	sprite->addKeyframe(DESENFUNDA_LEFT, glm::vec2(0.2f, 0.6f));
	sprite->addKeyframe(DESENFUNDA_LEFT, glm::vec2(0.3f, 0.6f));
	sprite->addKeyframe(DESENFUNDA_LEFT, glm::vec2(0.4f, 0.6f));
	sprite->addKeyframe(DESENFUNDA_LEFT, glm::vec2(0.5f, 0.6f));

	sprite->setAnimationSpeed(DESENFUNDA_RIGHT, 8);
	sprite->addKeyframe(DESENFUNDA_RIGHT, glm::vec2(-0.3f, 0.6f));
	sprite->addKeyframe(DESENFUNDA_RIGHT, glm::vec2(-0.4f, 0.6f));
	sprite->addKeyframe(DESENFUNDA_RIGHT, glm::vec2(-0.5f, 0.6f));
	sprite->addKeyframe(DESENFUNDA_RIGHT, glm::vec2(-0.6f, 0.6f));

	sprite->setAnimationSpeed(AMOVE_LEFT_FORWARD, 8);
	sprite->addKeyframe(AMOVE_LEFT_FORWARD, glm::vec2(0.6f, 0.6f));
	sprite->addKeyframe(AMOVE_LEFT_FORWARD, glm::vec2(0.7f, 0.6f));
	sprite->addKeyframe(AMOVE_LEFT_FORWARD, glm::vec2(0.8f, 0.6f));

	sprite->setAnimationSpeed(AMOVE_LEFT_BACK, 7);
	sprite->addKeyframe(AMOVE_LEFT_BACK, glm::vec2(0.9f, 0.6f));
	sprite->addKeyframe(AMOVE_LEFT_BACK, glm::vec2(0.f, 0.65f));

	sprite->setAnimationSpeed(AMOVE_RIGHT_FORWARD, 8);
	sprite->addKeyframe(AMOVE_RIGHT_FORWARD, glm::vec2(-0.7f, 0.6f));
	sprite->addKeyframe(AMOVE_RIGHT_FORWARD, glm::vec2(-0.8f, 0.6f));
	sprite->addKeyframe(AMOVE_RIGHT_FORWARD, glm::vec2(-0.9f, 0.6f));

	sprite->setAnimationSpeed(AMOVE_RIGHT_BACK, 7);
	sprite->addKeyframe(AMOVE_RIGHT_BACK, glm::vec2(-1.f, 0.6f));
	sprite->addKeyframe(AMOVE_RIGHT_BACK, glm::vec2(-0.1f, 0.65f));

	sprite->setAnimationSpeed(ATTACK_LEFT, 8);
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.1f, 0.65f));
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.2f, 0.65f));
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.3f, 0.65f));
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.4f, 0.65f));
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.5f, 0.65f));
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.6f, 0.65f));
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.7f, 0.65f));

	sprite->setAnimationSpeed(ATTACK_RIGHT, 8);
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(-0.2f, 0.65f));
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(-0.3f, 0.65f));
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(-0.4f, 0.65f));
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(-0.5f, 0.65f));
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(-0.6f, 0.65f));
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(-0.7f, 0.65f));
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(-0.8f, 0.65f));

	sprite->setAnimationSpeed(ENFUNDA_LEFT, 8);
	sprite->addKeyframe(ENFUNDA_LEFT, glm::vec2( 0.8f, 0.65f));
	sprite->addKeyframe(ENFUNDA_LEFT, glm::vec2(0.9f, 0.65f));
	sprite->addKeyframe(ENFUNDA_LEFT, glm::vec2(0.f, 0.7f));
	sprite->addKeyframe(ENFUNDA_LEFT, glm::vec2(0.1f, 0.7f));
	sprite->addKeyframe(ENFUNDA_LEFT, glm::vec2(0.2f, 0.7));
	sprite->addKeyframe(ENFUNDA_LEFT, glm::vec2(0.3f, 0.7f));
	sprite->addKeyframe(ENFUNDA_LEFT, glm::vec2(0.4f, 0.7f));
	sprite->addKeyframe(ENFUNDA_LEFT, glm::vec2(0.5f, 0.7f));
	sprite->addKeyframe(ENFUNDA_LEFT, glm::vec2(0.6f, 0.7f));

	sprite->setAnimationSpeed(ENFUNDA_RIGHT, 8);
	sprite->addKeyframe(ENFUNDA_RIGHT, glm::vec2(-0.9f, 0.65f));
	sprite->addKeyframe(ENFUNDA_RIGHT, glm::vec2(-1.f, 0.65f));
	sprite->addKeyframe(ENFUNDA_RIGHT, glm::vec2(-0.1f, 0.7f));
	sprite->addKeyframe(ENFUNDA_RIGHT, glm::vec2(-0.2f, 0.7f));
	sprite->addKeyframe(ENFUNDA_RIGHT, glm::vec2(-0.3f, 0.7));
	sprite->addKeyframe(ENFUNDA_RIGHT, glm::vec2(-0.4f, 0.7f));
	sprite->addKeyframe(ENFUNDA_RIGHT, glm::vec2(-0.5f, 0.7f));
	sprite->addKeyframe(ENFUNDA_RIGHT, glm::vec2(-0.6f, 0.7f));
	sprite->addKeyframe(ENFUNDA_RIGHT, glm::vec2(-0.7f, 0.7f));

	sprite->setAnimationSpeed(DEATHPINX_LEFT, 8);
	sprite->addKeyframe(DEATHPINX_LEFT, glm::vec2(0.7f, 0.7f));

	sprite->setAnimationSpeed(DEATHPINX_RIGHT, 8);
	sprite->addKeyframe(DEATHPINX_RIGHT, glm::vec2(-0.8f, 0.7f));

	sprite->setAnimationSpeed(DEATHENEMY_LEFT, 8);
	sprite->addKeyframe(DEATHENEMY_LEFT, glm::vec2(0.8f, 0.7f));
	sprite->addKeyframe(DEATHENEMY_LEFT, glm::vec2(0.9f, 0.7f));
	sprite->addKeyframe(DEATHENEMY_LEFT, glm::vec2(0.f, 0.75f));
	sprite->addKeyframe(DEATHENEMY_LEFT, glm::vec2(0.1f, 0.75f));
	sprite->addKeyframe(DEATHENEMY_LEFT, glm::vec2(0.2f, 0.75f));

	sprite->setAnimationSpeed(DEATHENEMY_RIGHT, 8);
	sprite->addKeyframe(DEATHENEMY_RIGHT, glm::vec2(-0.9f, 0.7f));
	sprite->addKeyframe(DEATHENEMY_RIGHT, glm::vec2(-1.f, 0.7f));
	sprite->addKeyframe(DEATHENEMY_RIGHT, glm::vec2(-0.1f, 0.75f));
	sprite->addKeyframe(DEATHENEMY_RIGHT, glm::vec2(-0.2f, 0.75f));
	sprite->addKeyframe(DEATHENEMY_RIGHT, glm::vec2(-0.3f, 0.75f));

	sprite->setAnimationSpeed(DEATHFALL_LEFT, 8);
	sprite->addKeyframe(DEATHFALL_LEFT, glm::vec2(0.3f, 0.75f));

	sprite->setAnimationSpeed(DEATHFALL_RIGHT, 8);
	sprite->addKeyframe(DEATHFALL_RIGHT, glm::vec2(-0.4f, 0.75f));

	sprite->changeAnimation(0);
	star->changeAnimation(OFF);
	teEspasa = true;
	cd_star = 0;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x+posPlayer.x), float(tileMapDispl.y+posPlayer.y)));
	star->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime)
{
	int dist;
	sprite->update(deltaTime);
	int frame = sprite->getFrame();
	int s = sprite->animation();
	direction = s % 2 == 0 ? "left" : "right";
	switch (s){
	case STAND_LEFT:
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(112) && !map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(SLOW_LEFT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(START_LEFT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(STANDLR);
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(JUMP_LEFT);
		if (bCombat) sprite->changeAnimation(DESENFUNDA_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_LEFT);
			falldist = posPlayer.y;
		}
		break;

	case STAND_RIGHT:
			if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(112) && !map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(SLOW_RIGHT);
			else if (Game::instance().getSpecialKey(GLUT_KEY_UP) && Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(SJUMP_RIGHT_START);
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(START_RIGHT);
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) sprite->changeAnimation(STANDRL);
			else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(JUMP_RIGHT);
			if (bCombat) sprite->changeAnimation(DESENFUNDA_RIGHT);
			if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
				sprite->changeAnimation(FALL_RIGHT);
				falldist = posPlayer.y;
			}
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
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_LEFT);
			falldist = posPlayer.y;

		}
		break;

	case START_RIGHT:
		if (frame == 0 && Game::instance().getSpecialKey(GLUT_KEY_UP) && Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(SJUMP_RIGHT_START);
		if (frame >= 4)posPlayer.x += 1;
		if (sprite->animFinished() && Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(MOVE_RIGHT);
		else if (sprite->animFinished()) sprite->changeAnimation(STOP_RIGHT);

		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_RIGHT);
			falldist = posPlayer.y;
		}
		break;

	case MOVE_LEFT:
		posPlayer.x -= 1;
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(RJUMP_LEFT_START);
		if (sprite->animFinished() && !Game::instance().getSpecialKey(GLUT_KEY_LEFT)) sprite->changeAnimation(STOP_LEFT);
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_LEFT);
			falldist = posPlayer.y;
		}

		break;

	case MOVE_RIGHT:
		posPlayer.x += 1;
		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(RJUMP_RIGHT_START);
		if (sprite->animFinished() && !Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) sprite->changeAnimation(STOP_RIGHT);
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_RIGHT);
			falldist = posPlayer.y;
		}
		break;

	case STOP_LEFT:
		posPlayer.x -= 1;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_LEFT);
			falldist = posPlayer.y;
		}

		break;

	case STOP_RIGHT:
		posPlayer.x += 1;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_RIGHT);
			falldist = posPlayer.y;
		}
		break;

	case SLOW_LEFT:
		if (frame > 2 && frame <5)posPlayer.x -= 1;
		else if (frame >= 8 && frame <= 10) posPlayer.x -= 1;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_LEFT);
			falldist = posPlayer.y;
		}
		break;

	case SLOW_RIGHT:
		if (frame >2 && frame<5)posPlayer.x += 1;
		else if (frame >= 8 && frame <= 10) posPlayer.x += 1;
		if (sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_RIGHT);
			falldist = posPlayer.y;
		}
		break;

	case JUMP_LEFT:
		if (frame == 0 && Game::instance().getSpecialKey(GLUT_KEY_UP) && Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(SJUMP_LEFT_START);
		if (frame>10) posPlayer.y--;
		if(sprite->animFinished()){
			if (map->JumpableLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(JUMP_LEFT_CATCH);
			else sprite->changeAnimation(JUMP_LEFT_FAIL);
		}
		break;

	case JUMP_RIGHT:
		if (frame == 0 && Game::instance().getSpecialKey(GLUT_KEY_UP) && Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(SJUMP_RIGHT_START);
		if (frame>10) posPlayer.y--;
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
		dist = (posPlayer.y - falldist) / 64;
		if (dist > 2) this->damage(dist, "FALL");
		else if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_LEFT);
			falldist = posPlayer.y;
		}
		break;

	case STAND_UP_RIGHT:
		dist = (posPlayer.y - falldist) / 64;
		if (dist > 2) this->damage(dist, "FALL");
		else if(sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_RIGHT);
			falldist = posPlayer.y;
		}
		break;

	case SJUMP_LEFT_START:
		if (frame >= 7) posPlayer.x -= 2;
		if (sprite->animFinished()){
			if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(SJUMP_LEFT_END);
			else {
				sprite->changeAnimation(FALL_LEFT);
				falldist = posPlayer.y;
			}
		}
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		break;

	case SJUMP_RIGHT_START:
		if (frame >= 7) posPlayer.x += 2;
		if (sprite->animFinished()){
			if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(SJUMP_RIGHT_END);
			else {
				sprite->changeAnimation(FALL_RIGHT);
				falldist = posPlayer.y;
			}
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
			if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
				sprite->changeAnimation(FALL_LEFT);
				falldist = posPlayer.y;
			}
		}
		else posPlayer.x -= 2;
		if (sprite->animFinished()){
			if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(RJUMP_LEFT_END);
			else{
				sprite->changeAnimation(FALL_LEFT);
				falldist = posPlayer.y;
			}
		}
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_LEFT);
		break;

	case RJUMP_RIGHT_START:
		if (frame <= 4) {
			posPlayer.x += 1;
			if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
				sprite->changeAnimation(FALL_RIGHT);
				falldist = posPlayer.y;
			}
		}
		else posPlayer.x += 2;
		if (sprite->animFinished()){
			if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) sprite->changeAnimation(RJUMP_RIGHT_END);
			else {
				sprite->changeAnimation(FALL_RIGHT);
				falldist = posPlayer.y;
			}
		}
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(STAND_RIGHT);
		break;

	case RJUMP_LEFT_END:
		if (sprite->animFinished()) sprite->changeAnimation(MOVE_LEFT);
		break;

	case RJUMP_RIGHT_END:
		if (sprite->animFinished()) sprite->changeAnimation(MOVE_RIGHT);
		break;

	case DESENFUNDA_LEFT:
		if (sprite->animFinished()) sprite->changeAnimation(ENGARDE_LEFT);
		break;

	case DESENFUNDA_RIGHT:
		if (sprite->animFinished()) sprite->changeAnimation(ENGARDE_RIGHT);
		break;

	case ENGARDE_LEFT:
		if (Game::instance().getSpecialKey(112)) sprite->changeAnimation(ATTACK_LEFT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(AMOVE_LEFT_FORWARD); //fa falta mirar colisions costat on em moc?
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(AMOVE_LEFT_BACK);
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(BLOCK_LEFT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) sprite->changeAnimation(ENFUNDA_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_LEFT);
			falldist = posPlayer.y;
		}
		if (!bCombat) sprite->changeAnimation(ENFUNDA_LEFT);
		break;

	case ENGARDE_RIGHT:
		if (Game::instance().getSpecialKey(112)) sprite->changeAnimation(ATTACK_RIGHT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(AMOVE_RIGHT_FORWARD); //fa falta mirar colisions costat on em moc?
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(AMOVE_RIGHT_BACK);
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(BLOCK_RIGHT);
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) sprite->changeAnimation(ENFUNDA_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_RIGHT);
			falldist = posPlayer.y;
		}
		if (!bCombat) sprite->changeAnimation(ENFUNDA_RIGHT);
		break;

	case AMOVE_LEFT_FORWARD:
		posPlayer.x -= 1;
		if (sprite->animFinished() || map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(ENGARDE_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_LEFT);
			falldist = posPlayer.y;
		}
		break;

	case AMOVE_RIGHT_FORWARD:
		posPlayer.x += 1;
		if (sprite->animFinished() || map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(ENGARDE_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_RIGHT);
			falldist = posPlayer.y;
		}
		break;

	case AMOVE_LEFT_BACK:
		posPlayer.x += 1;
		if (sprite->animFinished() || map->collisionMoveRight(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(ENGARDE_LEFT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_LEFT);
			falldist = posPlayer.y;
		}
		break;

	case AMOVE_RIGHT_BACK:
		posPlayer.x -= 1;
		if (sprite->animFinished() || map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64))) sprite->changeAnimation(ENGARDE_RIGHT);
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y)){
			sprite->changeAnimation(FALL_RIGHT);
			falldist = posPlayer.y;
		}
		break;

	case BLOCK_LEFT:
		if (sprite->animFinished()) sprite->changeAnimation(ENGARDE_LEFT);
		break;

	case BLOCK_RIGHT:
		if (sprite->animFinished()) sprite->changeAnimation(ENGARDE_RIGHT);
		break;

	case ATTACK_LEFT:
		if (frame == 2 || frame == 3) posPlayer.x -= 1;
		else if (frame == 4 || frame==5) posPlayer.x += 1;
		if (sprite->animFinished()) sprite->changeAnimation(ENGARDE_LEFT);
		break;

	case ATTACK_RIGHT:
		if (frame == 2 || frame == 3) posPlayer.x += 1;
		else if (frame == 4 || frame==5) posPlayer.x -= 1;
		if (sprite->animFinished()) sprite->changeAnimation(ENGARDE_RIGHT);
		break;

	case ENFUNDA_LEFT:
		if (sprite->animFinished()) sprite->changeAnimation(STAND_LEFT);
		break;

	case ENFUNDA_RIGHT:
		if (sprite->animFinished()) sprite->changeAnimation(STAND_RIGHT);
		break;

	case DEATHENEMY_LEFT:
		if (sprite->animFinished()) sprite->changeAnimation(DEATHFALL_LEFT);
		break;

	case DEATHENEMY_RIGHT:
		if (sprite->animFinished()) sprite->changeAnimation(DEATHFALL_RIGHT);
		break;

	}

	if (star->animation() == ON) cd_star += deltaTime;
	if (star->animation() == ON && cd_star >= CD_STAR) star->changeAnimation(OFF);

	//faltarien uns bools o funcions per saber estats del attack del player
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	star->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
	star->render();
}

glm::vec2 Player::getPosition()
{
	return posPlayer;
}

int Player::getHP()
{
	return hp;
}

void Player::damage(int amount, string type) //aquest string es per saber quin tipus d'animació de mort farem
{
	if (type == "enemy") {
		cd_star = 0;
		star->changeAnimation(ON);
	}
	hp = fmax(hp - amount, 0);
	dead = hp == 0;
	if (dead){
		if (type == "PINXO"){
			if (direction == "left") sprite->changeAnimation(DEATHPINX_LEFT);
			else sprite->changeAnimation(DEATHPINX_RIGHT);
		}
		else if (type == "FALL"){
			if (direction == "left")sprite->changeAnimation(DEATHFALL_LEFT);
			else sprite->changeAnimation(DEATHFALL_RIGHT);
		}
		else {
			if (direction == "left") sprite->changeAnimation(DEATHENEMY_LEFT);
			else sprite->changeAnimation(DEATHENEMY_RIGHT);
		}//animació mort per enemic**/

	}
}

void Player::heal(int amount){
	hp = fmin(MAX_LIFE, hp + amount);
}

bool Player::isDead()
{
	return dead;
}

bool Player::isAttacking()
{
	int frame = sprite->getFrame();
	return (frame == 5) && (sprite->animation() == ATTACK_LEFT || sprite->animation() == ATTACK_RIGHT); 
}

bool Player::isAttackingLong()
{
	return sprite->animation() == ATTACK_LEFT || sprite->animation() == ATTACK_RIGHT;
}

bool Player::isBlocking()
{
	return sprite->animation() == BLOCK_LEFT || sprite->animation() == BLOCK_RIGHT;
}
void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	star->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::setCombat(bool combat)
{
	bCombat = combat;
}

void Player::getSword()
{
	
}




