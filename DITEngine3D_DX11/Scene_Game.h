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
	GameObject* Muffler;
	GameObject* Engine_Transmission;
	GameObject* Tank;
	GameObject* Frame;
	GameObject* Sphere;
	GameObject* RearFender_Cover;
	GameObject* Suspension;
	GameObject* Carburetor;
	GameObject* Radiator;
	GameObject* RearAxle;
	GameObject* RearSuspension;
	GameObject* Wheel;
	GameObject* Tire;
	GameObject* Metor;
	GameObject* Metor_BackGround;
	GameObject* Seat;
	GameObject* Ground;

public:
	void Start();
	void Update();
	void Draw();
};