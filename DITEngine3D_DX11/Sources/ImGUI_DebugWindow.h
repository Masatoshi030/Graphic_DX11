#pragma once
#include "ImGUIWindowBase.h"
#include "Time.h"

class ImGUI_DebugWindow : public ImGUIWindowBase
{
public:

	void Init();
	~ImGUI_DebugWindow();

	void Draw_WindowSetting();
	void Draw_ItemSetting();


	//=== ï\é¶çÄñ⁄ ===//
	int FPS;
	TIME GameTime;

	float UI_Position_X_Slider;
	float UI_Position_Y_Slider;

	float UI_Rotation_Slider;

	float UI_Scale_X_Slider;
	float UI_Scale_Y_Slider;

	Vector4 Light_Diffuse;
	Vector4 Light_Ambient;
	Vector3 Light_Direction;
};