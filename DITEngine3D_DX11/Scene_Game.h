#pragma once
#include "GameObject.h"
#include "Scene.h"

class Scene_Game : public Scene
{
private:
	GameObject* MainCamera;
	GameObject* LightCamera;
	GameObject* SkyBox;
	GameObject* Cube;
	GameObject* Cube_Child;
	GameObject* Ground;

public:
	void Start();
	void Update();
	void Draw();
};