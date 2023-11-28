#pragma once
#include "Component.h"
#include "SystemFormat.h"
#include "utftosjisconv.h"
#include <string>
#include <unordered_map>
#include "ShaderManager.h"

//==========================================//
//		���b�V����`�悷��R���|�[�l���g	//
//==========================================//


// �}�e���A���\����
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;
};


// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// ���f���\����
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

	Shader::SHADER_ELEMENT* ShaderType;

public:

	static void Preload(const char* _FileName);
	static void UnloadAll();

	void Load(const char* _FileName, const char* _ShaderName);

	void Draw();
};