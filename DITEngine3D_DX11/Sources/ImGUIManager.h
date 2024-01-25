#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

#include <Windows.h>
#include <list>

#include "ImGUIWindowBase.h"

class ImGUIManager
{
private:

public:
	static void Init(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	static void Draw();
	static void Shutdown();

	static void AddWindow(ImGUIWindowBase* _Window);
};