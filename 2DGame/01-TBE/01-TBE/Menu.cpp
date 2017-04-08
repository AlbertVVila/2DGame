#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Menu.h"
#include "Game.h"
#include "windows.h"
#include "mmsystem.h"

#define CD 200

enum MenuAnims
{
	OPT1, OPT2, OPT3, OPT4, INSTS, CREDITS, INIT, END
};

Menu::Menu()
{
	
}

Menu::~Menu()
{

}


void Menu::init()
{
	initShaders();
	menuON = true;
	bplay = true;
	song_cd = 25000;

	spritesheet.setWrapS(GL_MIRRORED_REPEAT);
	spritesheet.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(320, 200), glm::vec2(1, 0.125), &spritesheet, &texProgram);
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(OPT1, 8);
	sprite->addKeyframe(OPT1, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(OPT2, 8);
	sprite->addKeyframe(OPT2, glm::vec2(0.0f, 0.125f));

	sprite->setAnimationSpeed(OPT3, 8);
	sprite->addKeyframe(OPT3, glm::vec2(0.0f, 0.25f));

	sprite->setAnimationSpeed(OPT4, 8);
	sprite->addKeyframe(OPT4, glm::vec2(0.0f, 0.375f));

	sprite->setAnimationSpeed(INSTS, 8);
	sprite->addKeyframe(INSTS, glm::vec2(0.0f, 0.5f));

	sprite->setAnimationSpeed(CREDITS, 8);
	sprite->addKeyframe(CREDITS, glm::vec2(0.0f, 0.625f));

	sprite->setAnimationSpeed(INIT, 8);
	sprite->addKeyframe(INIT, glm::vec2(0.0f, 0.75f));

	sprite->setAnimationSpeed(END, 8);
	sprite->addKeyframe(END, glm::vec2(0.0f, 0.875f));

	sprite->changeAnimation(OPT1);

	sprite->setPosition(glm::vec2(0,0));
	cd = 0;
	projection = glm::ortho(0.f, float(32*10 - 1), float(64*3 - 1), 0.f);
}

void Menu::update(int deltaTime)
{
	int anim = sprite->animation();
	if (anim != END && song_cd >= 25000) { song_cd = 0; PlaySound(TEXT("music/intro_theme.wav"), NULL, SND_ASYNC); }
	else if (anim == END && song_cd >= 115000) { song_cd = 0; PlaySound(TEXT("music/won.wav"), NULL, SND_ASYNC); }
	else song_cd += deltaTime;
	cd += deltaTime;
	if (cd >= CD)
		switch (anim){
		case OPT1:
			if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) { cd = 0; sprite->changeAnimation(OPT2); }
			else if (Game::instance().getKey(13)) { cd = 0; sprite->changeAnimation(INIT); }
			break;
		case OPT2:
			if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) { cd = 0; sprite->changeAnimation(OPT3); }
			else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) { cd = 0; sprite->changeAnimation(OPT1); }
			else if (Game::instance().getKey(13)) { cd = 0; sprite->changeAnimation(INSTS); }
			break;
		case OPT3:
			if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) { cd = 0; sprite->changeAnimation(OPT4); }
			else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) { cd = 0; sprite->changeAnimation(OPT2); }
			else if (Game::instance().getKey(13)) { cd = 0; sprite->changeAnimation(CREDITS); }
			break;
		case OPT4:
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) { cd = 0; sprite->changeAnimation(OPT3); }
			else if (Game::instance().getKey(13)) bplay = false;
			break;
		case INSTS:
			if (Game::instance().getKey(13)) { cd = 0; sprite->changeAnimation(OPT1); }
			break;
		case CREDITS:
			if (Game::instance().getKey(13)) { cd = 0; sprite->changeAnimation(OPT1); }
			break;
		case INIT:
			if (Game::instance().getKey(13)) { cd = 0; menuON = false; PlaySound(NULL, NULL, SND_ASYNC); }
			break;
		case END:
			if (Game::instance().getKey(13)) { cd = 0; sprite->changeAnimation(OPT1); PlaySound(TEXT("music/intro_theme.wav"), NULL, SND_ASYNC); }
			break;
		}
}

void Menu::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	sprite->render();
}

void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Menu::getBmenu()
{
	return menuON;
}

bool Menu::getBplay()
{
	return bplay;
}

void Menu::setEnd()
{
	sprite->changeAnimation(END);
	song_cd = 115000;
	menuON = true;
}