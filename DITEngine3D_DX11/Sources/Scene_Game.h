#pragma once

#include "Scene.h"

#include "Texture.h"

#include "ImGUI_WorldSettingWindow.h"
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

	Texture* SheetNormalMap;
	Texture* RoadNormalMap;
	Texture* TestNoise_MetallicMap;

	//ImGUIWindow
	ImGUI_WorldSettingWindow* ig_WorldSettingWindow;
	ImGUI_MaterialWindow* ig_MaterialWindow;

public:

	void Start();
	void Update();
	void Draw();
	void Release();
};