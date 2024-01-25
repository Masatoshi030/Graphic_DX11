#pragma once
#include "ImGUIWindowBase.h"
#include "Time.h"
#include "Direct3D11.h"
#include "MeshRenderer.h"
#include <list>

struct MATERIAL_EDITOR
{
	const char* materialName;

	std::list<MATERIAL*> SameMaterialList;

	Vector4 BaseColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	float Metaric = 0.0f;
	float Smoothness = 0.01f;
};

class ImGUI_MaterialWindow : public ImGUIWindowBase
{

private:

	MATERIAL_EDITOR* CheckDuplication(const char* _name);

public:

	void Init();
	~ImGUI_MaterialWindow();

	void Draw_WindowSetting();
	void Draw_ItemSetting();

	void AddMaterialEditor_MeshRenderer(MeshRenderer* _meshRenderer);
	void AddMaterialEditor(const char* _materinalName, MATERIAL* _material);
};