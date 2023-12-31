#pragma once
#include "GameObject.h"
#include "Scene.h"

class Scene_Game : public Scene
{
private:
	GameObject* PointLight_Obj;
	GameObject* MainCamera;
	GameObject* LightCamera;
	GameObject* SkyBox;

	GameObject* Body;
	GameObject* Muffler;
	GameObject* Engine;
	GameObject* Handle;
	GameObject* FrontFender;
	GameObject* FrontTire;
	GameObject* RearTire;

	GameObject* Sphere;

	GameObject* Ground;

public:
	void Start();
	void Update();
	void Draw();
};