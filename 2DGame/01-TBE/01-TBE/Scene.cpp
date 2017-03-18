#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 10
#define INIT_PLAYER_Y_TILES 0

Scene::Scene()
{
	background = NULL;
	ground_wall = NULL;
	other_column_back = NULL;
	player = NULL;
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
	if (player != NULL)
		delete player;
	if (other_column_front != NULL)
		delete other_column_front;
}


void Scene::init()
{
	initShaders();
	background = TileMap::createTileMap("levels/level1_1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	ground_wall = TileMap::createTileMap("levels/level1_2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	other_column_back = TileMap::createTileMap("levels/level1_3.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	other_column_front = TileMap::createTileMap("levels/level1_4.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram); 
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * ground_wall->getTileSizeW(), INIT_PLAYER_Y_TILES * ground_wall->getTileSizeH()));
	player->setTileMap(ground_wall);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
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
	player->render();
	other_column_front->render();
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



