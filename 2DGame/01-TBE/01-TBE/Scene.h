#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Vizier.h"
#include "Fat.h"
#include "Torch.h"
#include "Falling.h"
#include "Spikes.h"
#include "Door.h"
#include "Button.h"
#include "Sword.h"
#include "Clock.h"
#include "Potion.h"
#include "Life.h"

#define CAMERA_WIDTH 60*32	
#define CAMERA_HEIGHT 15*64


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	int getCurrentLvl();

private:
	void initShaders();
	void initlevel1();
	void initlevel2();
	void changelevel(int level);

private:
	int ndoors, nfallings, nbuttons, npotions, nfats, nviziers,ntorchs, nspikes;
	int currentlvl=1;
	TileMap *background, *ground_wall, *other_column_back, *other_column_front;
	Player *player;
	Vizier *viziers;
	Fat *fats;
	Torch *torchs;
	Falling *fallings;
	Spikes *spikes;
	Door *doors;
	Button *buttons;
	Sword *sword;
	Clock *clocks;
	Potion *potions;
	Life *life;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	glm::vec2 nextLevelPos;
};


#endif // _SCENE_INCLUDE

