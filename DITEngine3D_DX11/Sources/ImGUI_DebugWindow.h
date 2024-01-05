#pragma once
#include "ImGUIWindowBase.h"
#include "Time.h"

class ImGUI_DebugWindow : public ImGUIWindowBase
{
public:

	void Draw_WindowSetting();
	void Draw_ItemSetting();


	//=== ï\é¶çÄñ⁄ ===//
	int FPS;
	TIME GameTime;
};