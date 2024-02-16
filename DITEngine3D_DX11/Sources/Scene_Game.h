#pragma once

#include "Scene.h"

#include "ImGUI_DebugWindow.h"
#include "ImGUI_MaterialWindow.h"
#include "ImGUI_DisneyMaterialEditWindow.h"

class Scene_Game : public Scene
{
private:
	GameObject* DirectionalLight_Obj;
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

	GameObject* Studio_Bypass[5];

	GameObject* Sphere;

	GameObject* TestUI;

	GameObject* SuspensionSpring;

	//ImGUIWindow
	ImGUI_DebugWindow* ig_DebugWindow;
	ImGUI_MaterialWindow* ig_MaterialWindow;

public:

	void Start();
	void Update();
	void Draw();
};