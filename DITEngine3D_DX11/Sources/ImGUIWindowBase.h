#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

#include "SystemFormat.h"

//ImGUIでWindow管理用のベースクラス
class ImGUIWindowBase
{
public:

	char WindowName[32];

	void SetWindowName(const char* _WindowName);

	virtual void Init() {};

	virtual ~ImGUIWindowBase() {};

	virtual void Draw_WindowSetting() {};
	virtual void Draw_ItemSetting() {};
};