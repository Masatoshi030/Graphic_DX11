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

	Disney_Material.SubSurface.x = FileLoader::IniLoad_Float("Material_1", "SubSurfase", "Disney_Material");

	Disney_Material.Specular.x = FileLoader::IniLoad_Float("Material_1", "Specular", "Disney_Material");

	Disney_Material.SpecularTint.x = FileLoader::IniLoad_Float("Material_1", "SpecularTint", "Disney_Material");

	Disney_Material.Roughness.x = FileLoader::IniLoad_Float("Material_1", "Roughness", "Disney_Material");

	Disney_Material.Anisotropic.x = FileLoader::IniLoad_Float("Material_1", "Anisotropic", "Disney_Material");

	Disney_Material.Anisotropic_X.x = FileLoader::IniLoad_Float("Material_1", "Anisotropic_X_X", "Disney_Material");
	Disney_Material.Anisotropic_X.y = FileLoader::IniLoad_Float("Material_1", "Anisotropic_X_Y", "Disney_Material");
	Disney_Material.Anisotropic_X.z = FileLoader::IniLoad_Float("Material_1", "Anisotropic_X_Z", "Disney_Material");

	Disney_Material.Anisotropic_Y.x = FileLoader::IniLoad_Float("Material_1", "Anisotropic_Y_X", "Disney_Material");
	Disney_Material.Anisotropic_Y.y = FileLoader::IniLoad_Float("Material_1", "Anisotropic_Y_Y", "Disney_Material");
	Disney_Material.Anisotropic_Y.z = FileLoader::IniLoad_Float("Material_1", "Anisotropic_Y_Z", "Disney_Material");

	Disney_Material.Sheen.x = FileLoader::IniLoad_Float("Material_1", "Sheen", "Disney_Material");

	Disney_Material.SheenTint.x = FileLoader::IniLoad_Float("Material_1", "SheenTint", "Disney_Material");

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
	FileLoader::IniWrite("Material_1", "SubSurfase", Disney_Material.SubSurface.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Specular", Disney_Material.Specular.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "SpecularTint", Disney_Material.SpecularTint.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Roughness", Disney_Material.Roughness.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Anisotropic", Disney_Material.Anisotropic.x, "Disney_Material");

	FileLoader::IniWrite("Material_1", "Anisotropic_X_X", Disney_Material.Anisotropic_X.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Anisotropic_X_Y", Disney_Material.Anisotropic_X.y, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Anisotropic_X_Z", Disney_Material.Anisotropic_X.z, "Disney_Material");

	FileLoader::IniWrite("Material_1", "Anisotropic_Y_X", Disney_Material.Anisotropic_Y.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Anisotropic_Y_Y", Disney_Material.Anisotropic_Y.y, "Disney_Material");
	FileLoader::IniWrite("Material_1", "Anisotropic_Y_Z", Disney_Material.Anisotropic_Y.z, "Disney_Material");

	FileLoader::IniWrite("Material_1", "Sheen", Disney_Material.Sheen.x, "Disney_Material");
	FileLoader::IniWrite("Material_1", "SheenTint", Disney_Material.SheenTint.x, "Disney_Material");
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
	ImGui::SliderFloat("SubSurfase", &Disney_Material.SubSurface.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("Specular", &Disney_Material.Specular.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("SpecularTint", &Disney_Material.SpecularTint.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("Roughness", &Disney_Material.Roughness.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("Anisotropic", &Disney_Material.Anisotropic.x, 0.0f, 1.0f, "%.3f");


	Vector3 Anisotropic_X_buf;
	Anisotropic_X_buf = Vector3(Disney_Material.Anisotropic_X.x, Disney_Material.Anisotropic_X.y, Disney_Material.Anisotropic_X.z);

	ImGui::SliderFloat3("Anisotropic_X", Anisotropic_X_buf.float3, 0.0f, 1.0f, "%.3f");

	Disney_Material.Anisotropic_X.x = Anisotropic_X_buf.x;
	Disney_Material.Anisotropic_X.y = Anisotropic_X_buf.y;
	Disney_Material.Anisotropic_X.z = Anisotropic_X_buf.z;


	Vector3 Anisotropic_Y_buf;
	Anisotropic_Y_buf = Vector3(Disney_Material.Anisotropic_Y.x, Disney_Material.Anisotropic_Y.y, Disney_Material.Anisotropic_Y.z);

	ImGui::SliderFloat3("Anisotropic_Y", Anisotropic_Y_buf.float3, 0.0f, 1.0f, "%.3f");

	Disney_Material.Anisotropic_Y.x = Anisotropic_Y_buf.x;
	Disney_Material.Anisotropic_Y.y = Anisotropic_Y_buf.y;
	Disney_Material.Anisotropic_Y.z = Anisotropic_Y_buf.z;


	ImGui::SliderFloat("Sheen", &Disney_Material.Sheen.x, 0.0f, 1.0f, " % .3f");
	ImGui::SliderFloat("SheenTint", &Disney_Material.SheenTint.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("ClearCoat", &Disney_Material.ClearCoat.x, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("ClearCoatGloss", &Disney_Material.ClearCoatGloss.x, 0.0f, 1.0f, "%.3f");

}