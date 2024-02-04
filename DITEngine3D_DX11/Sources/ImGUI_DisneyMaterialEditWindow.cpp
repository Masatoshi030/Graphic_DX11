#include "ImGUI_DisneyMaterialEditWindow.h"
#include "Direct3D11.h"
#include "IniFileManager.h"

#include <stdio.h>

void ImGUI_DisneyMaterialEditWindow::Init()
{
	FileLoader::AddIniFilePath("Asset/data/Disney_Material.ini", "Disney_Material");

	Disney_Material.BaseColor.x = FileLoader::IniLoad_Float("Material_1", "BaseColor_R", "Disney_Material");
	Disney_Material.BaseColor.y = FileLoader::IniLoad_Float("Material_1", "BaseColor_G", "Disney_Material");
	Disney_Material.BaseColor.z = FileLoader::IniLoad_Float("Material_1", "BaseColor_B", "Disney_Material");
	Disney_Material.BaseColor.w = FileLoader::IniLoad_Float("Material_1", "BaseColor_A", "Disney_Material");

	Disney_Material.Metallic.x = FileLoader::IniLoad_Float("Material_1", "Metallic", "Disney_Material");

	Disney_Material.Specular.x = FileLoader::IniLoad_Float("Material_1", "Specular", "Disney_Material");

	Disney_Material.Roughness.x = FileLoader::IniLoad_Float("Material_1", "Roughness", "Disney_Material");

	Disney_Material.Anisotropic.x = FileLoader::IniLoad_Float("Material_1", "Anisotropic", "Disney_Material");

	Disney_Material.ClearCoat.x = FileLoader::IniLoad_Float("Material_1", "ClearCoat", "Disney_Material");

	Disney_Material.ClearCoatGloss.x = FileLoader::IniLoad_Float("Material_1", "ClearCoatGloss", "Disney_Material");
}

ImGUI_DisneyMaterialEditWindow::~ImGUI_DisneyMaterialEditWindow()
{

	FileLoader::IniWrite("Material_1", "BaseColor_R", Disney_Material.BaseColor.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "BaseColor_G", Disney_Material.BaseColor.y, "Disney_Material");
	FileLoader::IniWrite("Material_1", "BaseColor_B", Disney_Material.BaseColor.z, "Disney_Material");
	FileLoader::IniWrite("Material_1", "BaseColor_A", Disney_Material.BaseColor.w, "Disney_Material");

	FileLoader::IniWrite("Material_1", "Metallic", Disney_Material.Metallic.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Specular", Disney_Material.Specular.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Roughness", Disney_Material.Roughness.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Anisotropic", Disney_Material.Anisotropic.x, "Disney_Material");

	FileLoader::IniWrite("Material_1", "ClearCoat", Disney_Material.ClearCoat.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "ClearCoatGloss", Disney_Material.ClearCoatGloss.x, "Disney_Material");

}

void ImGUI_DisneyMaterialEditWindow::Draw_WindowSetting()
{

}

void ImGUI_DisneyMaterialEditWindow::Draw_ItemSetting()
{

	Vector4 BaseColor_buf;
	BaseColor_buf.simpleMath_vector4 = Disney_Material.BaseColor;

	ImGui::ColorPicker4("BaseColor", BaseColor_buf.float4, 0);

	Disney_Material.BaseColor = BaseColor_buf.simpleMath_vector4;

	ImGui::SliderFloat("Metallic", &Disney_Material.Metallic.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("Specular", &Disney_Material.Specular.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("Roughness", &Disney_Material.Roughness.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("Anisotropic", &Disney_Material.Anisotropic.x, 0.0f, 1.0f, "%.3f");

	ImGui::SliderFloat("ClearCoat", &Disney_Material.ClearCoat.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("ClearCoatGloss", &Disney_Material.ClearCoatGloss.x, 0.0f, 1.0f, "%.3f");

}