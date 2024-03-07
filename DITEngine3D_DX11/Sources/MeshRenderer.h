#pragma once
#include "Component.h"
#include "SystemFormat.h"
#include "utftosjisconv.h"
#include <string>
#include <unordered_map>
#include "ShaderManager.h"

//==========================================//
//		メッシュを描画するコンポーネント	//
//==========================================//


// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];

	DISNEY_MATERIAL		Disney_Material;

	char						TextureName[256];
	ID3D11VertexShader*			VertexShader;
	ID3D11InputLayout*			InputLayout;
	ID3D11PixelShader*			PixelShader;
	ID3D11ShaderResourceView*	Texture;
	ID3D11ShaderResourceView*	NormalMap;
	ID3D11ShaderResourceView*	MetallicMap;
};


// 描画サブセット構造体
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// モデル構造体
struct MODEL_OBJ
{
	VERTEX_3D* VertexArray;
	unsigned int	VertexNum;

	unsigned int* IndexArray;
	unsigned int	IndexNum;

	SUBSET* SubsetArray;
	unsigned int	SubsetNum;
};

struct MODEL
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;

	SUBSET* SubsetArray;
	unsigned int	SubsetNum;
};

class MeshRenderer : public Component
{

private:

	static std::unordered_map<std::string, MODEL*> ModelPool;
	
	static void LoadModel(const char* _FileName, MODEL* _Model);
	static void LoadObj(const char* _FileName, MODEL_OBJ* _ModelObj);
	static void LoadMaterial(const char* _FileName, MODEL_MATERIAL** _MaterialArray, unsigned int* _MaterialNum);

	MODEL* Model{};

public:

	static void Preload(const char* _FileName);
	static void Release();

	void Load(const char* _FileName);

	MODEL* GetModel()
	{
		return Model;
	}

	//=====================================================
	//マテリアル格納番号からサブセットを取得
	SUBSET* GetSubset_Index(int _idx)
	{
		return &Model->SubsetArray[_idx];
	}

	//=====================================================
	//マテリアル名からサブセットを取得
	SUBSET* GetSubset_MaterialName(const char* _name);

	void Draw();

	
};