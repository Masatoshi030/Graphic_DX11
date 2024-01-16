#pragma once

#include "Scene.h"

#include "ImGUI_DebugWindow.h"
#include "ImGUI_MaterialWindow.h"

class Scene_Game : public Scene
{
private:
	GameObject* DirectionalLight_Obj;
	GameObject* MainCamera;
	GameObject* SkyBox;

	GameObject* Sphere;

	GameObject* TestUI;

	//ImGUIWindow
	ImGUI_DebugWindow* ig_DebugWindow;
	ImGUI_MaterialWindow* ig_MaterialWindow;

public:

	void Start();
	void Update();
	void Draw();
};