#include "ImGUI_DebugWindow.h"

#include <stdio.h>

void ImGUI_DebugWindow::Draw_WindowSetting()
{

}

void ImGUI_DebugWindow::Draw_ItemSetting()
{
	//FPS表示
	ImGui::Text("FPS: %d", FPS);

	//実行時間表示
	ImGui::Text(
		"Time: %d:%d:%d:%d", 
		GameTime.Hour, 
		GameTime.Minutes, 
		GameTime.Second, 
		GameTime.MMSecond
	);
}