#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Vizier.h"
#include "Torch.h"
#include "Falling.h"
#include "Spikes.h"
#include "Door.h"
#include "Button.h"

#define CAMERA_WIDTH 60*32	
#define CAMERA_HEIGHT 12*64


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

private:
	void initShaders();

private:
	TileMap *background, *ground_wall, *other_column_back, *other_column_front;
	Player *player;
	Vizier *viziers;
	Torch *torchs;
	Falling *fallings;
	Spikes *spikes;
	Door *doors;
	Button *buttons;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

