#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include "Sprite.h"
#include <glm/glm.hpp>
#include "ShaderProgram.h"


// Menu represents the initial window with options


class Menu
{

public:
	Menu();
	~Menu();


	void init();
	void update(int deltaTime);
	void render();
	bool getMenuON();
	bool getBplay();

private:
	void initShaders();

private:
	ShaderProgram texProgram;
	Texture spritesheet;
	Sprite *sprite;
	glm::mat4 projection;
	bool menuON, bplay;
	float cd;
};


#endif // _MENU_INCLUDE
