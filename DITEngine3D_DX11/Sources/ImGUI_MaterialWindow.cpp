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
		e.Smoothness = FileLoader::IniLoad_Float(e.materialName, "Smoothness", "MaterialData");
	}


	//�ǂݍ��񂾃}�e���A���f�[�^��K�p
	for (auto& e : MaterialList)
	{
		for (auto& f : e.SameMaterialList)
		{
			f->Diffuse = DirectX::SimpleMath::Color(e.BaseColor.xmfloat4);
			f->Metalic.x = e.Metaric;
			f->Shininess = e.Smoothness;
		}
	}
}

void ImGUI_MaterialWindow::Draw_WindowSetting()
{

}

void ImGUI_MaterialWindow::Draw_ItemSetting()
{
	//== �}�e���A����� ==//

	for (auto& e : MaterialList)
	{
		if (ImGui::TreeNode(e.materialName))
		{
			ImGui::Text("BaseColor");
			ImGui::ColorPicker4("Diffuse", e.BaseColor.float4, 0);

			ImGui::Text("Metaric");
			ImGui::SliderFloat("Metaric", &e.Metaric, 0.0f, 1.0f);

			ImGui::Text("Smoothness");
			ImGui::SliderFloat("Smoothness", &e.Smoothness, 0.01f, 1.0f);

			for (auto& f : e.SameMaterialList)
			{
				f->Diffuse = DirectX::SimpleMath::Color(e.BaseColor.xmfloat4);
				f->Metalic.x = e.Metaric;
				f->Shininess = e.Smoothness;
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
			&_meshRenderer->GetSubset_Index(i)->Material.Material
		);
	}
}

void ImGUI_MaterialWindow::AddMaterialEditor(const char* _materinalName, MATERIAL* _material)
{
	//�d���`�F�b�N
	MATERIAL_EDITOR* materialEditor_buf = CheckDuplication(_materinalName);

	//�d���Ȃ�
	if (materialEditor_buf == nullptr)
	{
		MATERIAL_EDITOR materialEditor;

		//�}�e���A������ݒ�
		materialEditor.materialName = _materinalName;

		//�}�e���A������ݒ�
		materialEditor.SameMaterialList.push_back(_material);

		//���X�g�Ƀ}�e���A���ҏW����ǉ�
		MaterialList.push_back(materialEditor);
	}
	//�d������
	else
	{
		//�����̃}�e���A���̃��X�g�Ɋi�[
		materialEditor_buf->SameMaterialList.push_back(_material);
	}
}

MATERIAL_EDITOR* ImGUI_MaterialWindow::CheckDuplication(const char* _name)
{
	for (auto& e : MaterialList)
	{
		//���O����v�����
		if (strcmp(e.materialName, _name) == 0)
		{
			return &e;
		}
	}

	return nullptr;
}

//�ۑ�����
ImGUI_MaterialWindow::~ImGUI_MaterialWindow()
{
	for (auto& e : MaterialList)
	{
		FileLoader::IniWrite(e.materialName, "BaseColor_R", e.BaseColor.float4[0], "MaterialData");
		FileLoader::IniWrite(e.materialName, "BaseColor_G", e.BaseColor.float4[1], "MaterialData");
		FileLoader::IniWrite(e.materialName, "BaseColor_B", e.BaseColor.float4[2], "MaterialData");
		FileLoader::IniWrite(e.materialName, "BaseColor_A", e.BaseColor.float4[3], "MaterialData");

		FileLoader::IniWrite(e.materialName, "Metaric", e.Metaric, "MaterialData");
		FileLoader::IniWrite(e.materialName, "Smoothness", e.Smoothness, "MaterialData");
	}
}