#pragma once

#include "Scene.h"

#include "ImGUI_DebugWindow.h"

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

	GameObject* TestUI;

	GameObject* Ground;

	//ImGUIWindow
	ImGUI_DebugWindow* ig_DebugWindow;

public:

	void Start();
	void Update();
	void Draw();
};