#pragma once
#include "ImGUIWindowBase.h"
#include "Time.h"
#include "Direct3D11.h"
#include "MeshRenderer.h"
#include <list>

struct MATERIAL_EDITOR
{
	const char* materialName;

	std::list<DISNEY_MATERIAL*> SameMaterialList;

	Vector4 BaseColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	float Metaric = 0.0f;
	float Specular = 0.0f;
	float Roughness = 0.01f;
	float Anisotropic = 0.0f;
	float ClearCoat = 0.0f;
	float ClearCoatGloss = 0.0f;
	float NormalMap_Intensity = 0.0f;
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
	void AddMaterialEditor(const char* _materinalName, DISNEY_MATERIAL* _material);
};