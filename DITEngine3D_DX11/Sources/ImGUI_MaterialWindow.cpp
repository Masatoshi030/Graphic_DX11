#include "ImGUI_MaterialWindow.h"
#include "Direct3D11.h"

#include <stdio.h>

void ImGUI_MaterialWindow::Draw_WindowSetting()
{

}

void ImGUI_MaterialWindow::Draw_ItemSetting()
{
	//== É}ÉeÉäÉAÉãèÓïÒ ==//

	ImGui::Text("BaseColor");
	ImGui::ColorPicker4("Diffuse", BaseColor.float4, 0);
	material.Diffuse = DirectX::SimpleMath::Color(BaseColor.xmfloat4);

	ImGui::Text("Ambient");
	ImGui::ColorPicker4("Ambient", Ambient.float4);
	material.Ambient = DirectX::SimpleMath::Color(Ambient.xmfloat4);

	ImGui::Text("Metaric");
	ImGui::SliderFloat("Metaric", &Metaric, 0.0f, 1.0f);
	material.Metalic.x = Metaric;

	ImGui::Text("Smoothness");
	ImGui::SliderFloat("Smoothness", &Smoothness, 0.01f, 1.0f);
	material.Shininess = Smoothness;

	ImGui::Text("Specular");
	ImGui::ColorPicker4("Specular", Specular.float4);
	material.Specular = DirectX::SimpleMath::Color(Specular.xmfloat4);
}