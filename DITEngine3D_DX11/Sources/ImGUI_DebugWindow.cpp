#include "ImGUI_DebugWindow.h"

#include <stdio.h>

void ImGUI_DebugWindow::Draw_WindowSetting()
{

}

void ImGUI_DebugWindow::Draw_ItemSetting()
{
	//FPS�\��
	ImGui::Text("FPS: %d", FPS);

	//���s���ԕ\��
	ImGui::Text(
		"Time: %d:%d:%d:%d", 
		GameTime.Hour, 
		GameTime.Minutes, 
		GameTime.Second, 
		GameTime.MMSecond
	);
}