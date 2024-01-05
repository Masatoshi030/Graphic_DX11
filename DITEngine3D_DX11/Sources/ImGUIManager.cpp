#include "ImGuiManager.h"

std::list<ImGUIWindowBase*> WindowList;

void ImGUIManager::Init(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(device, deviceContext);
}

void ImGUIManager::Draw()
{

	// (Your code process and dispatch Win32 messages)
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (const auto& e : WindowList)
	{
		//�F�̕ύX
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.1f, 0.5f, 0.9f, 1.0f));

		//�E�B���h�E���̂̐ݒ�
		e->Draw_WindowSetting();

		//�E�B���h�E�J�n
		ImGui::Begin(e->WindowName);

		//���ڂ̐ݒ�
		e->Draw_ItemSetting();

		//�E�B���h�E�I��
		ImGui::End();

		ImGui::PopStyleColor();
	}


	// Rendering
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// (Your code calls swapchain's Present() function)
}

void ImGUIManager::Shutdown()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	for (const auto& e : WindowList)
	{
		delete e;
	}
}

void ImGUIManager::AddWindow(ImGUIWindowBase* _Window)
{
	WindowList.push_back(_Window);
};