#define _CRT_SECURE_NO_WARNINGS

#include "DITEngine3D.h"
#include "DITEngineSystem.h"
#include <stdio.h>
#include <shlwapi.h>
#include <WICTextureLoader.h>
#pragma comment(lib, "shlwapi.lib")

#include "WinMain.h"

using namespace DirectX;

std::unordered_map<std::string, MODEL*> MeshRenderer::ModelPool;

void MeshRenderer::Draw()
{

	D3D->SetWorldMatrix(&gameObject->transform->worldMatrix);


	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	D3D->Get_ID3D11DeviceContext()->IASetVertexBuffers(0, 1, &Model->VertexBuffer, &stride, &offset);

	//�C���f�b�N�X�o�b�t�@�ݒ�
	D3D->Get_ID3D11DeviceContext()->IASetIndexBuffer(Model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//�v���~�e�B�u�g�|���W�ݒ�
	D3D->Get_ID3D11DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (unsigned int i = 0; i < Model->SubsetNum; i++)
	{
		//== �}�e���A����ݒ� ==//

		//���^���b�N��0.00f�ɂȂ�Ȃ��悤�ɂ���
		if (Model->SubsetArray[i].Material.Material.Metalic.x < 0.1f)
		{
			Model->SubsetArray[i].Material.Material.Metalic.x = 0.1f;
		}

		if (Model->SubsetArray[i].Material.Material.Shininess < 0.1f)
		{
			Model->SubsetArray[i].Material.Material.Shininess = 0.1f;
		}

		D3D->SetMaterial(Model->SubsetArray[i].Material.Material);

		//== �}�e���A�����ƂɃV�F�[�_�[��ݒ� ==//

		// ���̓��C�A�E�g�ݒ�
		D3D->Get_ID3D11DeviceContext()->IASetInputLayout(Model->SubsetArray[i].Material.InputLayout);

		// �V�F�[�_�ݒ�
		D3D->Get_ID3D11DeviceContext()->VSSetShader(Model->SubsetArray[i].Material.VertexShader, NULL, 0);
		D3D->Get_ID3D11DeviceContext()->PSSetShader(Model->SubsetArray[i].Material.PixelShader, NULL, 0);


		//== �e�N�X�`���ݒ� ==//
		if (Model->SubsetArray[i].Material.Texture)
		{
			D3D->Get_ID3D11DeviceContext()->PSSetShaderResources(1, 1, &Model->SubsetArray[i].Material.Texture);
		}


		//== �X�y�L�����[���x�ɉ������~�b�v���x���̊��e�N�X�`����ݒ� ==//
		
		MipMap* environmentTexture_MipMap = DITEngine::GetEnvironmentMipMap();

		//�X�y�L�����[���x���ő�Ŋ����ăe�N�X�`���������|���邱�Ƃň�ԋ߂��~�b�v���x�����v�Z����
		int mipLevel = (1.00f - Model->SubsetArray[i].Material.Material.Shininess) * (environmentTexture_MipMap->GetTextureCount() - 1);

		//�e�N�X�`�����擾
		Texture* environmentTexture_Texture = environmentTexture_MipMap->GetTexture_MipLevel(mipLevel);

		//SRV���擾
		ID3D11ShaderResourceView* environmentTexture_srv = environmentTexture_Texture->GetResource();

		//�摜���s�N�Z���V�F�[�_�[�ɃZ�b�g
		D3D->Get_ID3D11DeviceContext()->PSSetShaderResources(0, 1, &environmentTexture_srv);

		//�摜�̏���ݒ�
		ENVIRONMENTMAP_INFO em_buf;
		em_buf.ImageSize.x = environmentTexture_Texture->GetWidth();	//�摜�̉𑜓x
		em_buf.ImageSize.y = environmentTexture_Texture->GetHeight();

		//�摜�̏����Z�b�g
		D3D->SetEnvironmentMapInfo(em_buf);


		//== �|���S���`�� ==//
		D3D->Get_ID3D11DeviceContext()->DrawIndexed(Model->SubsetArray[i].IndexNum, Model->SubsetArray[i].StartIndex, 0);
	}
}

void MeshRenderer::Preload(const char* _FileName)
{
	if (ModelPool.count(_FileName) > 0)
	{
		return;
	}

	MODEL* model = new MODEL;
	LoadModel(_FileName, model);

	ModelPool[_FileName] = model;
}

void MeshRenderer::Release()
{
	for (std::pair<const std::string, MODEL*> pair : ModelPool)
	{
		pair.second->VertexBuffer->Release();
		pair.second->IndexBuffer->Release();

		for (unsigned int i = 0; i < pair.second->SubsetNum; i++)
		{
			if (pair.second->SubsetArray[i].Material.Texture)
				pair.second->SubsetArray[i].Material.Texture->Release();
		}

		delete[] pair.second->SubsetArray;

		delete pair.second;
	}

	ModelPool.clear();
}

void MeshRenderer::Load(const char* _FileName)
{

	if (ModelPool.count(_FileName) > 0)
	{
		Model = ModelPool[_FileName];
		return;
	}

	Model = new MODEL;

	LoadModel(_FileName, Model);

	ModelPool[_FileName] = Model;

	//�x�[�X�̃V�F�[�_�[��ݒ�
	for (int i = 0; i < Model->SubsetNum; i++)
	{
		Model->SubsetArray[i].Material.InputLayout = Shader::GetInputLayout("Base");
		Model->SubsetArray[i].Material.VertexShader = Shader::GetVertexShader("Base");
		Model->SubsetArray[i].Material.PixelShader = Shader::GetPixelShader("Base");
	}
}

void MeshRenderer::LoadModel(const char* _FileName, MODEL* Model)
{

	MODEL_OBJ modelObj;
	LoadObj(_FileName, &modelObj);



	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * modelObj.VertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = modelObj.VertexArray;

		D3D->Get_ID3D11Device()->CreateBuffer(&bd, &sd, &Model->VertexBuffer);
	}


	// �C���f�b�N�X�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * modelObj.IndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = modelObj.IndexArray;

		D3D->Get_ID3D11Device()->CreateBuffer(&bd, &sd, &Model->IndexBuffer);
	}

	// �T�u�Z�b�g�ݒ�
	{
		Model->SubsetArray = new SUBSET[modelObj.SubsetNum];
		Model->SubsetNum = modelObj.SubsetNum;

		for (unsigned int i = 0; i < modelObj.SubsetNum; i++)
		{
			Model->SubsetArray[i].StartIndex = modelObj.SubsetArray[i].StartIndex;
			Model->SubsetArray[i].IndexNum = modelObj.SubsetArray[i].IndexNum;

			//���O�̃R�s�[
			strcpy(Model->SubsetArray[i].Material.Name, modelObj.SubsetArray[i].Material.Name);

			Model->SubsetArray[i].Material.Material = modelObj.SubsetArray[i].Material.Material;

			Model->SubsetArray[i].Material.Texture = nullptr;

			// s-jis�����C�h������
			std::wstring ws = sjis_to_wide_winapi(modelObj.SubsetArray[i].Material.TextureName);

			// �e�N�X�`���ǂݍ���
			DirectX::CreateWICTextureFromFile(
				D3D->Get_ID3D11Device(),
				//				modelObj.SubsetArray[i].Material.TextureName,
				ws.c_str(),
				nullptr,
				&Model->SubsetArray[i].Material.Texture);

			if (Model->SubsetArray[i].Material.Texture)
				Model->SubsetArray[i].Material.Material.TextureEnable = true;
			else
				Model->SubsetArray[i].Material.Material.TextureEnable = false;

		}
	}

	delete[] modelObj.VertexArray;
	delete[] modelObj.IndexArray;
	delete[] modelObj.SubsetArray;

}

//���f���Ǎ�
void MeshRenderer::LoadObj(const char* _FileName, MODEL_OBJ* _ModelObj)
{

	char dir[MAX_PATH];
	strcpy(dir, _FileName);
	PathRemoveFileSpec(dir);





	Vector3* positionArray;
	Vector3* normalArray;
	Vector2* texcoordArray;

	unsigned int	positionNum = 0;
	unsigned int	normalNum = 0;
	unsigned int	texcoordNum = 0;
	unsigned int	vertexNum = 0;
	unsigned int	indexNum = 0;
	unsigned int	in = 0;
	unsigned int	subsetNum = 0;

	MODEL_MATERIAL* materialArray = nullptr;
	unsigned int	materialNum = 0;

	char str[256];
	char* s;
	char c;


	FILE* file;
	file = fopen(_FileName, "rt");
	assert(file);



	//�v�f���J�E���g
	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "v") == 0)
		{
			positionNum++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			normalNum++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			texcoordNum++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			subsetNum++;
		}
		else if (strcmp(str, "f") == 0)
		{
			in = 0;

			do
			{
				fscanf(file, "%s", str);
				vertexNum++;
				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//�l�p�͎O�p�ɕ���
			if (in == 4)
				in = 6;

			indexNum += in;
		}
	}


	//�������m��
	positionArray = new Vector3[positionNum];
	normalArray = new Vector3[normalNum];
	texcoordArray = new Vector2[texcoordNum];


	_ModelObj->VertexArray = new VERTEX_3D[vertexNum];
	_ModelObj->VertexNum = vertexNum;

	_ModelObj->IndexArray = new unsigned int[indexNum];
	_ModelObj->IndexNum = indexNum;

	_ModelObj->SubsetArray = new SUBSET[subsetNum];
	_ModelObj->SubsetNum = subsetNum;




	//�v�f�Ǎ�
	Vector3* position = positionArray;
	Vector3* normal = normalArray;
	Vector2* texcoord = texcoordArray;

	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;


	fseek(file, 0, SEEK_SET);

	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "mtllib") == 0)
		{
			//�}�e���A���t�@�C��
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			LoadMaterial(path, &materialArray, &materialNum);
		}
		else if (strcmp(str, "o") == 0)
		{
			//�I�u�W�F�N�g��
			fscanf(file, "%s", str);
		}
		else if (strcmp(str, "v") == 0)
		{
			//���_���W
			fscanf(file, "%f", &position->x);
			fscanf(file, "%f", &position->y);
			fscanf(file, "%f", &position->z);

			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			//�@��
			fscanf(file, "%f", &normal->x);
			fscanf(file, "%f", &normal->y);
			fscanf(file, "%f", &normal->z);

			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			//�e�N�X�`�����W
			fscanf(file, "%f", &texcoord->x);
			fscanf(file, "%f", &texcoord->y);
			texcoord->x = 1.0f - texcoord->x;
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			//�}�e���A��
			fscanf(file, "%s", str);

			if (sc != 0)
				_ModelObj->SubsetArray[sc - 1].IndexNum = ic - _ModelObj->SubsetArray[sc - 1].StartIndex;

			_ModelObj->SubsetArray[sc].StartIndex = ic;


			for (unsigned int i = 0; i < materialNum; i++)
			{
				if (strcmp(str, materialArray[i].Name) == 0)
				{
					_ModelObj->SubsetArray[sc].Material.Material = materialArray[i].Material;
					strcpy(_ModelObj->SubsetArray[sc].Material.TextureName, materialArray[i].TextureName);
					strcpy(_ModelObj->SubsetArray[sc].Material.Name, materialArray[i].Name);

					break;
				}
			}

			sc++;

		}
		else if (strcmp(str, "f") == 0)
		{
			//��
			in = 0;

			do
			{
				fscanf(file, "%s", str);

				s = strtok(str, "/");
				_ModelObj->VertexArray[vc].Position = positionArray[atoi(s) - 1].simpleMath_vector3;
				
				if (s[strlen(s) + 1] != '/')
				{
					//�e�N�X�`�����W�����݂��Ȃ��ꍇ������
					s = strtok(nullptr, "/");
					_ModelObj->VertexArray[vc].TexCoord = texcoordArray[atoi(s) - 1].simpleMath_vector2;
				}
				s = strtok(nullptr, "/");
				_ModelObj->VertexArray[vc].Normal = normalArray[atoi(s) - 1].simpleMath_vector3;

				_ModelObj->VertexArray[vc].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);

				_ModelObj->IndexArray[ic] = vc;

				ic++;
				vc++;

				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//�l�p�͎O�p�ɕ���
			if (in == 4)
			{
				_ModelObj->IndexArray[ic] = vc - 4;
				ic++;
				_ModelObj->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}


	if (sc != 0)
		_ModelObj->SubsetArray[sc - 1].IndexNum = ic - _ModelObj->SubsetArray[sc - 1].StartIndex;


	fclose(file);


	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}


//�}�e���A���ǂݍ���
void MeshRenderer::LoadMaterial(const char* _FileName, MODEL_MATERIAL** _MaterialArray, unsigned int* _MaterialNum)
{

	char dir[MAX_PATH];
	strcpy(dir, _FileName);
	PathRemoveFileSpec(dir);



	char str[256];

	FILE* file;
	file = fopen(_FileName, "rt");
	assert(file);

	MODEL_MATERIAL* materialArray;
	unsigned int materialNum = 0;

	//�v�f���J�E���g
	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;


		if (strcmp(str, "newmtl") == 0)
		{
			materialNum++;
		}
	}


	//�������m��
	materialArray = new MODEL_MATERIAL[materialNum];


	//�v�f�Ǎ�
	int mc = -1;

	fseek(file, 0, SEEK_SET);

	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;


		if (strcmp(str, "newmtl") == 0)
		{
			//�}�e���A����
			mc++;
			fscanf(file, "%s", materialArray[mc].Name);
			strcpy(materialArray[mc].TextureName, "");

			materialArray[mc].Material.Emission.x = 0.0f;
			materialArray[mc].Material.Emission.y = 0.0f;
			materialArray[mc].Material.Emission.z = 0.0f;
			materialArray[mc].Material.Emission.w = 0.0f;
		}
		else if (strcmp(str, "Ka") == 0)
		{
			//�A���r�G���g
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.x);
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.y);
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.z);
			materialArray[mc].Material.Ambient.w = 1.0f;
		}
		else if (strcmp(str, "Kd") == 0)
		{
			//�f�B�t���[�Y
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.x);
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.y);
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.z);
			materialArray[mc].Material.Diffuse.w = 1.0f;
		}
		else if (strcmp(str, "Ks") == 0)
		{
			//�X�y�L����
			fscanf(file, "%f", &materialArray[mc].Material.Specular.x);
			fscanf(file, "%f", &materialArray[mc].Material.Specular.y);
			fscanf(file, "%f", &materialArray[mc].Material.Specular.z);
			materialArray[mc].Material.Specular.w = 1.0f;
		}
		else if (strcmp(str, "Ns") == 0)
		{
			//�X�y�L�������x
			fscanf(file, "%f", &materialArray[mc].Material.Shininess);

			materialArray[mc].Material.Shininess = (materialArray[mc].Material.Shininess / 1000.0f);
		}
		else if (strcmp(str, "d") == 0)
		{
			//�A���t�@
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.w);
		}
		else if (strcmp(str, "map_Kd") == 0)
		{
			//�e�N�X�`��
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			strcat(materialArray[mc].TextureName, path);
		}

		materialArray[mc].Material.Metalic.x = 1.0f;
	}

	fclose(file);

	*_MaterialArray = materialArray;
	*_MaterialNum = materialNum;
}

SUBSET* MeshRenderer::GetSubset_MaterialName(const char* _name)
{
	for (int i = 0; i < Model->SubsetNum; i++)
	{
		if (std::strcmp(Model->SubsetArray[i].Material.Name, _name) == 0)
		{
			return &Model->SubsetArray[i];
		}
	}

	return nullptr;
}