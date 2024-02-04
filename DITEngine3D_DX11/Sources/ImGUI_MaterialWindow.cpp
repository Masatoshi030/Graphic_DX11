#include "ImGUI_MaterialWindow.h"
#include "Direct3D11.h"
#include "IniFileManager.h"

#include <stdio.h>

std::list<MATERIAL_EDITOR> MaterialList;

void ImGUI_MaterialWindow::Init()
{
	FileLoader::AddIniFilePath("Asset/data/MateriaData.ini", "MaterialData");

	for (auto& e : MaterialList)
	{
		e.BaseColor.float4[0] = FileLoader::IniLoad_Float(e.materialName, "BaseColor_R", "MaterialData");
		e.BaseColor.float4[1] = FileLoader::IniLoad_Float(e.materialName, "BaseColor_G", "MaterialData");
		e.BaseColor.float4[2] = FileLoader::IniLoad_Float(e.materialName, "BaseColor_B", "MaterialData");
		e.BaseColor.float4[3] = FileLoader::IniLoad_Float(e.materialName, "BaseColor_A", "MaterialData");

		e.Metaric = FileLoader::IniLoad_Float(e.materialName, "Metaric", "MaterialData");
		e.Specular = FileLoader::IniLoad_Float(e.materialName, "Specular", "MaterialData");
		e.Roughness = FileLoader::IniLoad_Float(e.materialName, "Roughness", "MaterialData");
		e.Anisotropic = FileLoader::IniLoad_Float(e.materialName, "Anisotropic", "MaterialData");
		e.ClearCoat = FileLoader::IniLoad_Float(e.materialName, "ClearCoat", "MaterialData");
		e.ClearCoatGloss = FileLoader::IniLoad_Float(e.materialName, "ClearCoatGloss", "MaterialData");
	}


	//読み込んだマテリアルデータを適用
	for (auto& e : MaterialList)
	{
		for (auto& f : e.SameMaterialList)
		{
			f->BaseColor = DirectX::SimpleMath::Color(e.BaseColor.xmfloat4);
			f->Metallic.x = e.Metaric;
			f->Specular.x = e.Specular;
			f->Roughness.x = e.Roughness;
			f->Anisotropic.x = e.Anisotropic;
			f->ClearCoat.x = e.ClearCoat;
			f->ClearCoatGloss.x = e.ClearCoatGloss;
		}
	}
}

void ImGUI_MaterialWindow::Draw_WindowSetting()
{

}

void ImGUI_MaterialWindow::Draw_ItemSetting()
{
	//== マテリアル情報 ==//

	for (auto& e : MaterialList)
	{
		if (ImGui::TreeNode(e.materialName))
		{
			ImGui::Text("BaseColor");
			ImGui::ColorPicker4("Diffuse", e.BaseColor.float4, 0);

			ImGui::Text("Metaric");
			ImGui::SliderFloat("Metaric", &e.Metaric, 0.0f, 1.0f);

			ImGui::Text("Specular");
			ImGui::SliderFloat("Specular", &e.Specular, 0.0f, 1.0f);

			ImGui::Text("Roughness");
			ImGui::SliderFloat("Roughness", &e.Roughness, 0.01f, 1.0f);

			ImGui::Text("Anisotropic");
			ImGui::SliderFloat("Anisotropic", &e.Anisotropic, 0.01f, 1.0f);

			ImGui::Text("ClearCoat");
			ImGui::SliderFloat("ClearCoat", &e.ClearCoat, 0.01f, 1.0f);

			ImGui::Text("ClearCoatGloss");
			ImGui::SliderFloat("ClearCoatGloss", &e.ClearCoatGloss, 0.01f, 1.0f);

			for (auto& f : e.SameMaterialList)
			{
				f->BaseColor = DirectX::SimpleMath::Color(e.BaseColor.xmfloat4);
				f->Metallic.x = e.Metaric;
				f->Specular.x = e.Specular;
				f->Roughness.x = e.Roughness;
				f->Anisotropic.x = e.Anisotropic;
				f->ClearCoat.x = e.ClearCoat;
				f->ClearCoatGloss.x = e.ClearCoatGloss;
			}

			ImGui::TreePop();
		}
	}
}

void ImGUI_MaterialWindow::AddMaterialEditor_MeshRenderer(MeshRenderer* _meshRenderer)
{

	for (int i = 0; i < _meshRenderer->GetModel()->SubsetNum; i++)
	{
		AddMaterialEditor(
			_meshRenderer->GetSubset_Index(i)->Material.Name,
			&_meshRenderer->GetSubset_Index(i)->Material.Disney_Material
		);
	}
}

void ImGUI_MaterialWindow::AddMaterialEditor(const char* _materinalName, DISNEY_MATERIAL* _material)
{
	//重複チェック
	MATERIAL_EDITOR* materialEditor_buf = CheckDuplication(_materinalName);

	//重複なし
	if (materialEditor_buf == nullptr)
	{
		MATERIAL_EDITOR materialEditor;

		//マテリアル名を設定
		materialEditor.materialName = _materinalName;

		//マテリアル情報を設定
		materialEditor.SameMaterialList.push_back(_material);

		//リストにマテリアル編集情報を追加
		MaterialList.push_back(materialEditor);
	}
	//重複あり
	else
	{
		//既存のマテリアルのリストに格納
		materialEditor_buf->SameMaterialList.push_back(_material);
	}
}

MATERIAL_EDITOR* ImGUI_MaterialWindow::CheckDuplication(const char* _name)
{
	for (auto& e : MaterialList)
	{
		//名前が一致すれば
		if (strcmp(e.materialName, _name) == 0)
		{
			return &e;
		}
	}

	return nullptr;
}

//保存処理
ImGUI_MaterialWindow::~ImGUI_MaterialWindow()
{
	for (auto& e : MaterialList)
	{
		FileLoader::IniWrite(e.materialName, "BaseColor_R", e.BaseColor.float4[0], "MaterialData");
		FileLoader::IniWrite(e.materialName, "BaseColor_G", e.BaseColor.float4[1], "MaterialData");
		FileLoader::IniWrite(e.materialName, "BaseColor_B", e.BaseColor.float4[2], "MaterialData");
		FileLoader::IniWrite(e.materialName, "BaseColor_A", e.BaseColor.float4[3], "MaterialData");

		FileLoader::IniWrite(e.materialName, "Metaric", e.Metaric, "MaterialData");
		FileLoader::IniWrite(e.materialName, "Specular", e.Specular, "MaterialData");
		FileLoader::IniWrite(e.materialName, "Roughness", e.Roughness, "MaterialData");
		FileLoader::IniWrite(e.materialName, "Anisotropic", e.Anisotropic, "MaterialData");
		FileLoader::IniWrite(e.materialName, "ClearCoat", e.ClearCoat, "MaterialData");
		FileLoader::IniWrite(e.materialName, "ClearCoatGloss", e.ClearCoatGloss, "MaterialData");
	}
}