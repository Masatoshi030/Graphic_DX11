#include "ImGUI_DebugWindow.h"
#include "Direct3D11.h"
#include "IniFileManager.h"

#include <stdio.h>

void ImGUI_DebugWindow::Init()
{
	FileLoader::AddIniFilePath("Asset/data/DebugData.ini", "DebugData");

	UI_Position_X_Slider = FileLoader::IniLoad_Float("UI", "Position_X", "DebugData");
	UI_Position_Y_Slider = FileLoader::IniLoad_Float("UI", "Position_Y", "DebugData");

	UI_Rotation_Slider = FileLoader::IniLoad_Float("UI", "Rotation_Z", "DebugData");

	UI_Scale_X_Slider = FileLoader::IniLoad_Float("UI", "Scale_X", "DebugData");
	UI_Scale_Y_Slider = FileLoader::IniLoad_Float("UI", "Scale_Y", "DebugData");


	Light_Diffuse.float4[0] = FileLoader::IniLoad_Float("DirectionalLight", "Diffuse_R", "DebugData");
	Light_Diffuse.float4[1] = FileLoader::IniLoad_Float("DirectionalLight", "Diffuse_G", "DebugData");
	Light_Diffuse.float4[2] = FileLoader::IniLoad_Float("DirectionalLight", "Diffuse_B", "DebugData");
	Light_Diffuse.float4[3] = FileLoader::IniLoad_Float("DirectionalLight", "Diffuse_A", "DebugData");
	
	Light_Ambient.float4[0] = FileLoader::IniLoad_Float("DirectionalLight", "Ambient_R", "DebugData");
	Light_Ambient.float4[1] = FileLoader::IniLoad_Float("DirectionalLight", "Ambient_G", "DebugData");
	Light_Ambient.float4[2] = FileLoader::IniLoad_Float("DirectionalLight", "Ambient_B", "DebugData");
	Light_Ambient.float4[3] = FileLoader::IniLoad_Float("DirectionalLight", "Ambient_A", "DebugData");

	Light_Direction.float3[0] = FileLoader::IniLoad_Float("DirectionalLight", "Direction_X", "DebugData");
	Light_Direction.float3[1] = FileLoader::IniLoad_Float("DirectionalLight", "Direction_Y", "DebugData");
	Light_Direction.float3[2] = FileLoader::IniLoad_Float("DirectionalLight", "Direction_Z", "DebugData");
}

ImGUI_DebugWindow::~ImGUI_DebugWindow()
{

	FileLoader::IniWrite("UI", "Position_X", UI_Position_X_Slider, "DebugData");
	FileLoader::IniWrite("UI", "Position_Y", UI_Position_Y_Slider, "DebugData");

	FileLoader::IniWrite("UI", "Rotation_Z", UI_Rotation_Slider, "DebugData");

	FileLoader::IniWrite("UI", "Scale_X", UI_Scale_X_Slider, "DebugData");
	FileLoader::IniWrite("UI", "Scale_Y", UI_Scale_Y_Slider, "DebugData");


	FileLoader::IniWrite("DirectionalLight", "Diffuse_R", Light_Diffuse.float4[0], "DebugData");
	FileLoader::IniWrite("DirectionalLight", "Diffuse_G", Light_Diffuse.float4[1], "DebugData");
	FileLoader::IniWrite("DirectionalLight", "Diffuse_B", Light_Diffuse.float4[2], "DebugData");
	FileLoader::IniWrite("DirectionalLight", "Diffuse_A", Light_Diffuse.float4[3], "DebugData");
	
	FileLoader::IniWrite("DirectionalLight", "Ambient_R", Light_Ambient.float4[0], "DebugData");
	FileLoader::IniWrite("DirectionalLight", "Ambient_G", Light_Ambient.float4[1], "DebugData");
	FileLoader::IniWrite("DirectionalLight", "Ambient_B", Light_Ambient.float4[2], "DebugData");
	FileLoader::IniWrite("DirectionalLight", "Ambient_A", Light_Ambient.float4[3], "DebugData");
	
	FileLoader::IniWrite("DirectionalLight", "Direction_X", Light_Direction.float3[0], "DebugData");
	FileLoader::IniWrite("DirectionalLight", "Direction_Y", Light_Direction.float3[1], "DebugData");
	FileLoader::IniWrite("DirectionalLight", "Direction_Z", Light_Direction.float3[2], "DebugData");
}

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