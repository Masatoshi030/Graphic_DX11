#include "ImGUI_DebugWindow.h"
#include "Direct3D11.h"

#include <stdio.h>

void ImGUI_DebugWindow::Draw_WindowSetting()
{

}

void ImGUI_DebugWindow::Draw_ItemSetting()
{
	//== システム絵バッグ情報 ==//

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


	//== DirectionalLight ==//

	ImGui::Text("Position");
	ImGui::SliderFloat("p_X", &UI_Position_X_Slider, -(D3D->Get_ApplicationHandle()->Get_WindowWidth() * 0.5f), (D3D->Get_ApplicationHandle()->Get_WindowWidth() * 0.5f));
	ImGui::SliderFloat("p_Y", &UI_Position_Y_Slider, -(D3D->Get_ApplicationHandle()->Get_WindowHeight() * 0.5f), (D3D->Get_ApplicationHandle()->Get_WindowHeight() * 0.5f));

	ImGui::Text("Rotation");
	ImGui::SliderFloat("r_Z", &UI_Rotation_Slider, 0.0f, 90.0f);

	ImGui::Text("Scale");
	ImGui::SliderFloat("s_X", &UI_Scale_X_Slider, 0.0f, 10.0f);
	ImGui::SliderFloat("s_Y", &UI_Scale_Y_Slider, 0.0f, 10.0f);


	//== DirectionalLight ==//

	ImGui::Text("DirectionalLight");
	ImGui::ColorPicker4("Light_Diffuse", Light_Diffuse.float4, 0);
	ImGui::ColorPicker4("Light_Ambient", Light_Ambient.float4, 0);
	ImGui::SliderFloat3("Light_Direction", Light_Direction.float3, -1.0f, 1.0f, "%.3f");
}