#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 34
#define INIT_PLAYER_Y_TILES -1

#define INIT_PLAYER_X_TILES2 2
#define INIT_PLAYER_Y_TILES2 9.9

#define NUM_VIZIERS 2
#define NUM_FATS 0
#define NUM_TORCHS 23
#define NUM_FALLINGS 6
#define NUM_SPIKES 14
#define NUM_DOORS 5
#define NUM_BUTTONS 5
#define NUM_CLOCKS 2
#define NUM_POTIONS 2

#define NUM_TORCHS2 25
#define NUM_SPIKES2 16
#define NUM_POTIONS2 11
#define NUM_FALLINGS2 17
#define NUM_DOORS2 8
#define NUM_BUTTONS2 8
#define NUM_VIZIERS2 5
#define NUM_FATS2 4
Scene::Scene()
{
	background = NULL;
	ground_wall = NULL;
	other_column_back = NULL;
	torchs = NULL;
	fallings = NULL;
	spikes = NULL;
	doors = NULL;
	buttons = NULL;
	sword = NULL;
	clocks = NULL;
	potions = NULL;
	player = NULL;
	life = NULL;
	viziers = NULL;
	fats = NULL;
	other_column_front = NULL;
}

Scene::~Scene()
{
	if(background != NULL)
		delete background;
	if (ground_wall != NULL)
		delete ground_wall;
	if (other_column_back != NULL)
		delete other_column_back;
	if (torchs != NULL)
		delete torchs;
	if (fallings != NULL)
		delete fallings;
	if (spikes != NULL)
		delete spikes;
	if (doors != NULL)
		delete doors;
	if (buttons != NULL)
		delete buttons;
	if (sword != NULL)
		delete sword;
	if (clocks != NULL)
		delete clocks;
	if (potions != NULL)
		delete potions;
	if (viziers != NULL)
		delete viziers;
	if (fats != NULL)
		delete fats;
	if (player != NULL)
		delete player;
	if (life != NULL)
		delete life;
	if (other_column_front != NULL)
		delete other_column_front;
}


void Scene::init()
{
	initShaders();
	changelevel(currentlvl);
	//
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	projection = glm::ortho(0.f, 32 * 10.f, 64 * 3.f + 14, 0.f);
	currentTime = 0.0f;
}
void Scene::initlevel1(){
	background = TileMap::createTileMap("levels/level1_1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	ground_wall = TileMap::createTileMap("levels/level1_2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	other_column_back = TileMap::createTileMap("levels/level1_3.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	other_column_front = TileMap::createTileMap("levels/level1_4.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	torchs = new Torch[NUM_TORCHS];
	for (int i = 0; i < NUM_TORCHS; i++)
		torchs[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	torchs[0].setPosition(glm::vec2(75, -43));
	torchs[1].setPosition(glm::vec2(235, 21));
	torchs[2].setPosition(glm::vec2(427, 21));
	torchs[3].setPosition(glm::vec2(75, 213));
	torchs[4].setPosition(glm::vec2(75, 469));
	torchs[5].setPosition(glm::vec2(171, 469));
	torchs[6].setPosition(glm::vec2(235, 277));
	torchs[7].setPosition(glm::vec2(555, 85));
	torchs[8].setPosition(glm::vec2(843, 85));
	torchs[9].setPosition(glm::vec2(1131, 85));
	torchs[10].setPosition(glm::vec2(1131, -43));
	torchs[11].setPosition(glm::vec2(1195, -43));
	torchs[12].setPosition(glm::vec2(1643, -43));
	torchs[13].setPosition(glm::vec2(1643, 85));
	torchs[14].setPosition(glm::vec2(1643, 341));
	torchs[15].setPosition(glm::vec2(1515, 341));
	torchs[16].setPosition(glm::vec2(1547, 469));
	torchs[17].setPosition(glm::vec2(1803, 469));
	torchs[18].setPosition(glm::vec2(491, 469));
	torchs[19].setPosition(glm::vec2(715, 469));
	torchs[20].setPosition(glm::vec2(875, 533));
	torchs[21].setPosition(glm::vec2(1099, 405));
	torchs[22].setPosition(glm::vec2(1195, 405));
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * ground_wall->getTileSizeW(), INIT_PLAYER_Y_TILES * ground_wall->getTileSizeH()));
	player->setTileMap(ground_wall);
	fallings = new Falling[NUM_FALLINGS];
	for (int i = 0; i < NUM_FALLINGS; i++)
	{
		fallings[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram,"images/falling_sprite.png");
		fallings[i].setTileMap(ground_wall);
		fallings[i].setPlayer(player);
	}
	fallings[0].setPosition(glm::vec2(224, 64));
	fallings[1].setPosition(glm::vec2(544, 448));
	fallings[2].setPosition(glm::vec2(576, 448));
	fallings[3].setPosition(glm::vec2(288, 64));
	fallings[4].setPosition(glm::vec2(352, 64));
	fallings[5].setPosition(glm::vec2(832, 64));

	spikes = new Spikes[NUM_SPIKES];
	for (int i = 0; i < NUM_SPIKES; i++)
	{
		spikes[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		spikes[i].setPlayer(player);
	}
	spikes[0].setPosition(glm::vec2(544, 576));
	spikes[1].setPosition(glm::vec2(576, 576));
	spikes[2].setPosition(glm::vec2(544, 192));
	spikes[3].setPosition(glm::vec2(576, 192));
	spikes[4].setPosition(glm::vec2(672, 192));
	spikes[5].setPosition(glm::vec2(704, 192));
	spikes[6].setPosition(glm::vec2(1120, 256));
	spikes[7].setPosition(glm::vec2(192, 512));
	spikes[8].setPosition(glm::vec2(1248, 576));
	spikes[9].setPosition(glm::vec2(1824, 576));
	spikes[10].setPosition(glm::vec2(1856, 576));
	spikes[11].setPosition(glm::vec2(1664, 192));
	spikes[12].setPosition(glm::vec2(1760, 128));
	spikes[13].setPosition(glm::vec2(1568, 64));

	doors = new Door[NUM_DOORS];
	for (int i = 0; i < NUM_DOORS; i++){
		doors[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/door_sprite.png");
		doors[i].setTileMap(ground_wall);
	}
	doors[0].setPosition(glm::vec2(448, 64));
	doors[1].setPosition(glm::vec2(1120, 448));
	doors[2].setPosition(glm::vec2(1120, 0));
	doors[3].setPosition(glm::vec2(1696, 320));
	doors[4].setPosition(glm::vec2(1536, 448));

	doors[0].setTimeOpened(12000);
	doors[1].setTimeOpened(5000);
	doors[2].setTimeOpened(15000);
	doors[3].setTimeOpened(25000);
	doors[4].setTimeOpened(30000);

	buttons = new Button[NUM_BUTTONS];
	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		buttons[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/button_sprite.png");
		buttons[i].setPlayer(player);
	}
	buttons[0].setPosition(glm::vec2(736, 128));
	buttons[0].setDoor(&doors[0]);
	buttons[1].setPosition(glm::vec2(992, 448));
	buttons[1].setDoor(&doors[1]);
	buttons[2].setPosition(glm::vec2(1472, 128));
	buttons[2].setDoor(&doors[2]);
	buttons[3].setPosition(glm::vec2(1440, 384));
	buttons[3].setDoor(&doors[3]);
	buttons[4].setPosition(glm::vec2(1792, 512));
	buttons[4].setDoor(&doors[4]);

	sword = new Sword();
	sword->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	sword->setPlayer(player);
	sword->setPosition(glm::vec2(1738, 576));

	potions = new Potion[NUM_POTIONS];
	for (int i = 0; i < NUM_POTIONS; i++)
	{
		potions[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		potions[i].setPlayer(player);
	}
	potions[0].setPosition(glm::vec2(32, 0));
	potions[1].setPosition(glm::vec2(832, 576));

	clocks = new Clock[NUM_CLOCKS];
	for (int i = 0; i < NUM_CLOCKS; i++)
	{
		clocks[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		clocks[i].setPlayer(player);
	}
	clocks[0].setPosition(glm::vec2(1024, 320+8));
	clocks[0].setTarget(glm::vec2(1600, 0));
	clocks[1].setPosition(glm::vec2(1632, 8));
	clocks[1].setTarget(glm::vec2(1056, 320));

	viziers = new Vizier[NUM_VIZIERS];
	for (int i = 0; i < NUM_VIZIERS; i++)
	{
		viziers[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		viziers[i].setTileMap(ground_wall);
		viziers[i].setPlayer(player);
	}
	viziers[0].setPosition(glm::vec2(320, 312));
	viziers[1].setPosition(glm::vec2(320, 504));

	nextLevelPos = glm::vec2(96,512);

	life = new Life();
	life->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	life->setPlayer(player);
	life->setPosition(glm::vec2(0, 0));
}
void Scene::initlevel2(){
	background = TileMap::createTileMap("levels/level2_back.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	ground_wall = TileMap::createTileMap("levels/level2_ground.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	other_column_back = TileMap::createTileMap("levels/level2_back_col.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	other_column_front = TileMap::createTileMap("levels/level2_front_col.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	torchs = new Torch[NUM_TORCHS2];
	for (int i = 0; i < NUM_TORCHS2; i++)
		torchs[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	torchs[0].setPosition(glm::vec2(15 * 32 + 10, 4 * 64 - 43));
	torchs[1].setPosition(glm::vec2(23 * 32 + 10, 4 * 64 - 43));
	torchs[2].setPosition(glm::vec2(26 * 32 + 10, 4 * 64 - 43));
	torchs[3].setPosition(glm::vec2(32 * 32 + 10, 4 * 64 - 43));
	torchs[4].setPosition(glm::vec2(40 * 32 + 10, 4 * 64 - 43));
	torchs[5].setPosition(glm::vec2(45 * 32 + 10, 4 * 64 - 43));
	torchs[6].setPosition(glm::vec2(58 * 32 + 10, 5 * 64 - 43));
	torchs[7].setPosition(glm::vec2(57 * 32 + 10, 9 * 64 - 43));
	torchs[8].setPosition(glm::vec2(48 * 32 + 10, 9 * 64 - 43));
	torchs[9].setPosition(glm::vec2(58 * 32 + 10, 5 * 64 - 43));
	torchs[10].setPosition(glm::vec2(32 * 32 + 10, 11 * 64 - 43));
	torchs[11].setPosition(glm::vec2(20 * 32 + 10, 7 * 64 - 43));
	torchs[12].setPosition(glm::vec2(17 * 32 + 10, 8 * 64 - 43));
	torchs[13].setPosition(glm::vec2(12 * 32 + 10, 10 * 64 - 43));
	torchs[14].setPosition(glm::vec2(58 * 32 + 10, 5 * 64 - 43));
	torchs[15].setPosition(glm::vec2(58 * 32 + 10, 5 * 64 - 43));
	torchs[16].setPosition(glm::vec2(58 * 32 + 10, 5 * 64 - 43));
	torchs[17].setPosition(glm::vec2(5 * 32 + 10, 2 * 64 - 43));
	torchs[18].setPosition(glm::vec2(8 * 32 + 10, 2 * 64 - 43));
	torchs[19].setPosition(glm::vec2(2 * 32 + 10, 4 * 64 - 43));
	torchs[20].setPosition(glm::vec2(8 * 32 + 10, 7 * 64 - 43));
	torchs[21].setPosition(glm::vec2(5 * 32 + 10, 9 * 64 - 43));
	torchs[22].setPosition(glm::vec2(45 * 32 + 10, 7 * 64 - 43));
	torchs[23].setPosition(glm::vec2(17 * 32 + 10, 10 * 64 - 43));
	torchs[24].setPosition(glm::vec2(14 * 32 + 10, 7 * 64 - 43));

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->getSword();
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES2 * ground_wall->getTileSizeW(), INIT_PLAYER_Y_TILES2 * ground_wall->getTileSizeH()));
	player->setTileMap(ground_wall);

	fallings = new Falling[NUM_FALLINGS2];
	for (int i = 0; i < NUM_FALLINGS2; i++)
	{
		fallings[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/falling2.png");
		fallings[i].setTileMap(ground_wall);
		fallings[i].setPlayer(player);
	}
	fallings[0].setPosition(glm::vec2(7 * 32, 10 * 64));
	fallings[1].setPosition(glm::vec2(8 * 32, 10 * 64));
	fallings[2].setPosition(glm::vec2(5 * 32, 7 * 64));
	fallings[3].setPosition(glm::vec2(5 * 32, 4 * 64));
	fallings[4].setPosition(glm::vec2(6 * 32, 4 * 64));
	fallings[5].setPosition(glm::vec2(7 * 32, 4 * 64));
	fallings[6].setPosition(glm::vec2(11 * 32, 8 * 64));
	fallings[7].setPosition(glm::vec2(12 * 32, 8 * 64));
	fallings[8].setPosition(glm::vec2(20 * 32, 7 * 64));
	fallings[9].setPosition(glm::vec2(21 * 32, 7 * 64));
	fallings[10].setPosition(glm::vec2(24 * 32, 10 * 64));
	fallings[11].setPosition(glm::vec2(25 * 32, 10 * 64));
	fallings[12].setPosition(glm::vec2(23 * 32, 4 * 64));
	fallings[13].setPosition(glm::vec2(24 * 32, 4 * 64));
	fallings[14].setPosition(glm::vec2(20 * 32, 7 * 64));
	fallings[15].setPosition(glm::vec2(21 * 32, 7 * 64));
	fallings[16].setPosition(glm::vec2(48 * 32, 4 * 64));

	spikes = new Spikes[NUM_SPIKES2];
	for (int i = 0; i < NUM_SPIKES2; i++)
	{
		spikes[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		spikes[i].setPlayer(player);
	}
	spikes[0].setPosition(glm::vec2(2 * 32, 2 * 64));
	spikes[1].setPosition(glm::vec2(3 * 32, 2 * 64));
	spikes[2].setPosition(glm::vec2(5 * 32, 9 * 64));
	spikes[3].setPosition(glm::vec2(3 * 32, 13 * 64));
	spikes[4].setPosition(glm::vec2(6 * 32, 13 * 64));
	spikes[5].setPosition(glm::vec2(15 * 32, 4 * 64));
	spikes[6].setPosition(glm::vec2(21 * 32, 4 * 64));
	spikes[7].setPosition(glm::vec2(24 * 32, 13 * 64));
	spikes[8].setPosition(glm::vec2(25 * 32, 13 * 64));
	spikes[9].setPosition(glm::vec2(32 * 32, 4 * 64));
	spikes[10].setPosition(glm::vec2(40 * 32, 11 * 64));
	spikes[11].setPosition(glm::vec2(41 * 32, 7 * 64));
	spikes[12].setPosition(glm::vec2(45 * 32, 7 * 64));
	spikes[13].setPosition(glm::vec2(51 * 32, 9 * 64));
	spikes[14].setPosition(glm::vec2(57 * 32, 9 * 64));
	spikes[15].setPosition(glm::vec2(1 * 32, 7 * 64));

	doors = new Door[NUM_DOORS2];
	for (int i = 0; i < NUM_DOORS2; i++){
		doors[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/door2.png");
		doors[i].setTileMap(ground_wall);
	}
	doors[0].setPosition(glm::vec2(9 * 32, 4 * 64-10));
	doors[1].setPosition(glm::vec2(9 * 32, 10 * 64-10));
	doors[2].setPosition(glm::vec2(19 * 32, 10 * 64-10));
	doors[3].setPosition(glm::vec2(19 * 32, 7 * 64-10));
	doors[4].setPosition(glm::vec2(29 * 32, 4 * 64-10));
	doors[5].setPosition(glm::vec2(29 * 32, 7 * 64-10));
	doors[6].setPosition(glm::vec2(39 * 32, 10 * 64-10));
	doors[7].setPosition(glm::vec2(49 * 32, 11 * 64-10));

	doors[0].setTimeOpened(12000);
	doors[1].setTimeOpened(5000);
	doors[2].setTimeOpened(15000);
	doors[3].setTimeOpened(25000);
	doors[4].setTimeOpened(30000);
	doors[5].setTimeOpened(30000);
	doors[6].setTimeOpened(30000);
	doors[7].setTimeOpened(30000);

	buttons = new Button[NUM_BUTTONS2];
	for (int i = 0; i < NUM_BUTTONS2; i++)
	{
		buttons[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/button2.png");
		buttons[i].setPlayer(player);
	}
	buttons[0].setPosition(glm::vec2(12 * 32, 4 * 64));
	buttons[0].setDoor(&doors[0]);
	buttons[1].setPosition(glm::vec2(6 * 32, 10 * 64));
	buttons[1].setDoor(&doors[1]);
	buttons[2].setPosition(glm::vec2(15 * 32, 10 * 64));
	buttons[2].setDoor(&doors[2]);
	buttons[3].setPosition(glm::vec2(27 * 32, 7 * 64));
	buttons[3].setDoor(&doors[3]);
	buttons[4].setPosition(glm::vec2(33 * 32, 4 * 64));
	buttons[4].setDoor(&doors[4]);
	buttons[5].setPosition(glm::vec2(22 * 32, 7 * 64));
	buttons[5].setDoor(&doors[5]);
	buttons[6].setPosition(glm::vec2(33 * 32, 11 * 64));
	buttons[6].setDoor(&doors[6]);
	buttons[7].setPosition(glm::vec2(43 * 32, 11 * 64));
	buttons[7].setDoor(&doors[7]);

	potions = new Potion[NUM_POTIONS2];
	for (int i = 0; i < NUM_POTIONS2; i++)
	{
		potions[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		potions[i].setPlayer(player);
	}
	potions[0].setPosition(glm::vec2(8 * 32, 4 * 64));
	potions[1].setPosition(glm::vec2(14 * 32, 4 * 64));
	potions[2].setPosition(glm::vec2(25 * 32, 4 * 64));
	potions[3].setPosition(glm::vec2(51 * 32, 6 * 64));
	potions[4].setPosition(glm::vec2(43 * 32, 7 * 64));
	potions[5].setPosition(glm::vec2(39 * 32, 7 * 64));
	potions[6].setPosition(glm::vec2(29 * 32, 10 * 64));
	potions[7].setPosition(glm::vec2(20 * 32, 8 * 64));
	potions[8].setPosition(glm::vec2(19 * 32, 9 * 64));
	potions[9].setPosition(glm::vec2(47 * 32, 11 * 64));
	potions[10].setPosition(glm::vec2(4 * 32, 7 * 64));

	clocks = new Clock[NUM_CLOCKS];
	for (int i = 0; i < NUM_CLOCKS; i++)
	{
		clocks[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		clocks[i].setPlayer(player);
	}
	clocks[0].setPosition(glm::vec2(2 * 32, 13 * 64 + 10));
	clocks[0].setTarget(glm::vec2(43 * 32, 7 * 64));
	clocks[1].setPosition(glm::vec2(25 * 32 - 10, 12 * 64));
	clocks[1].setTarget(glm::vec2(58 * 32, 4 * 64));

	viziers = new Vizier[NUM_VIZIERS2];
	for (int i = 0; i < NUM_VIZIERS2; i++)
	{
		viziers[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		viziers[i].setTileMap(ground_wall);
		viziers[i].setPlayer(player);
	}
	viziers[0].setPosition(glm::vec2(18 * 32, 10 * 64 - 8));
	viziers[1].setPosition(glm::vec2(15 * 32, 7 * 64 - 8));
	viziers[2].setPosition(glm::vec2(29 * 32, 9 * 64 - 8));
	viziers[3].setPosition(glm::vec2(34 * 32, 11 * 64 - 8));
	viziers[4].setPosition(glm::vec2(50 * 32, 8 * 64 - 8));


	fats = new Fat[NUM_FATS2];
	for (int i = 0; i < NUM_FATS2; i++)
	{
		fats[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		fats[i].setTileMap(ground_wall);
		fats[i].setPlayer(player);
	}
	fats[0].setPosition(glm::vec2(54 * 32, 11 * 64 - 8));
	fats[1].setPosition(glm::vec2(38 * 32, 4 * 64 - 8));
	fats[2].setPosition(glm::vec2(26 * 32, 4 * 64 - 8));
	fats[3].setPosition(glm::vec2(1 * 32, 3 * 64 - 8));

	nextLevelPos = glm::vec2(192, 128);

	life = new Life();
	life->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	life->setPlayer(player);
	life->setPosition(glm::vec2(0, 0));

}
void Scene::update(int deltaTime)
{
	if (Game::instance().getKey(13)){ //enter key
		this->init();
	}
	if (Game::instance().getKey(108)) {
		currentlvl == 1 ? currentlvl = 2 : currentlvl = 1;
		changelevel(currentlvl);
	}
	if ((player->getPosition().y == nextLevelPos.y - 8) &&
		(player->getPosition().x - nextLevelPos.x) >= -27 &&
		(player->getPosition().x - nextLevelPos.x) < 25)
	{
		if (currentlvl == 1) currentlvl = 2;
		else if (currentlvl == 2) currentlvl = 3;
		changelevel(currentlvl);
	}
	currentTime += deltaTime;
	player->update(deltaTime);
	for (int i = 0; i < ntorchs; i++)
		torchs[i].update(deltaTime);
	for (int i = 0; i < nfallings; i++)
		fallings[i].update(deltaTime);
	for (int i = 0; i < nspikes; i++)
		spikes[i].update(deltaTime);
	for (int i = 0; i < ndoors; i++)
		doors[i].update(deltaTime);
	for (int i = 0; i < nbuttons; i++)
		buttons[i].update(deltaTime);
	if (currentlvl==1) sword->update(deltaTime);
	for (int i = 0; i < NUM_CLOCKS; i++)
		clocks[i].update(deltaTime);
	for (int i = 0; i < npotions; i++)
		potions[i].update(deltaTime);
	for (int i = 0; i < nviziers; i++)
		viziers[i].update(deltaTime);
	for (int i = 0; i < nfats; i++)
		fats[i].update(deltaTime);

	int panelX = int((player->getPosition().x-4+32) / 320.f);
	int panelY = int((player->getPosition().y+64) / 192.f);
	life->setPosition(glm::vec2(panelX * 32.f * 10, panelY * 64.f * 3 + 135));
	life->update(deltaTime);
	projection = glm::ortho(panelX * 32.f * 10, (panelX + 1) * 32.f * 10, (panelY + 1) * 64.f * 3 + 7, panelY * 64.f * 3);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
	ground_wall->render();
	other_column_back->render();
	for (int i = 0; i < ntorchs; i++)
		torchs[i].render();
	for (int i = 0; i < nfallings; i++)
		fallings[i].render();
	for (int i = 0; i < nspikes; i++)
		spikes[i].render();
	for (int i = 0; i < ndoors; i++)
		doors[i].render();
	for (int i = 0; i < nbuttons; i++)
		buttons[i].render();
	if (currentlvl == 1) sword->render();
	for (int i = 0; i < NUM_CLOCKS; i++)
		clocks[i].render();
	for (int i = 0; i < npotions; i++)
		potions[i].render();
	for (int i = 0; i < nviziers; i++)
		viziers[i].render();
	for (int i = 0; i < nfats; i++)
		fats[i].render();
		
	player->render();
	other_column_front->render();
	life->render();
}

void Scene::changelevel(int level){
	switch (level){
	case 1:
		initlevel1();
		ntorchs = NUM_TORCHS;
		npotions = NUM_POTIONS;
		nbuttons = NUM_BUTTONS;
		ndoors = NUM_DOORS;
		nfats = NUM_FATS;
		nfallings = NUM_FALLINGS;
		nviziers = NUM_VIZIERS;
		nspikes = NUM_SPIKES;
		break;
	case 2:
		initlevel2();
		ntorchs = NUM_TORCHS2;
		npotions = NUM_POTIONS2;
		nbuttons = NUM_BUTTONS2;
		ndoors = NUM_DOORS2;
		nfats = NUM_FATS2;
		nfallings = NUM_FALLINGS2;
		nviziers = NUM_VIZIERS2;
		nspikes = NUM_SPIKES2;
		break;
	}
}

int Scene::getCurrentLvl()
{
	return currentlvl;
}

void Scene::setCurrentLvl(int l)
{
	currentlvl = l;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



