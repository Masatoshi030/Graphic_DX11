#pragma once
#include "ImGUIWindowBase.h"
#include "Time.h"
#include "Direct3D11.h"

class ImGUI_MaterialWindow : public ImGUIWindowBase
{
private:
	Vector4 BaseColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4 Ambient = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	float Metaric = 0.0f;
	float Smoothness = 0.01f;
	Vector4 Specular = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

public:

	void Draw_WindowSetting();
	void Draw_ItemSetting();


	//=== ï\é¶çÄñ⁄ ===//

	MATERIAL material;

};