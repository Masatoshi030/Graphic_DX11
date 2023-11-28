#include "DITEngine3D.h"
#include "Scene_Game.h"

void Scene_Game::Start()
{
	//�V�F�[�_�[�ݒ�
	Shader::AddShader("Asset/shader/unlitTextureVS.cso", "Asset/shader/unlitTexturePS.cso", "Unlit");
	Shader::AddShader("Asset/shader/vertexLightingVS.cso", "Asset/shader/vertexLightingPS.cso", "Light");


	//�I�u�W�F�N�g�ݒ�

	//== ���C���J���� ==//
	MainCamera = new GameObject();

	MainCamera->AddComponent<Camera>();

	Hierarchy.push_back(MainCamera);


	//== �e�X�gBOX ==//
	SkyBox = new GameObject();

	SkyBox->AddComponent<MeshRenderer>()->Load("Asset\\model\\SkyBox_Town.obj", "Unlit");

	SkyBox->transform->scale.x = 30.0f;

	Hierarchy.push_back(SkyBox);


	//== �L���[�u ==//
	Cube = new GameObject();

	Cube->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Cube.obj", "Light");

	Hierarchy.push_back(Cube);

	Cube->transform->position.y = 1.0f;


	//== �n�� ==//
	Ground = new GameObject();

	Ground->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Ground.obj", "Light");

	Hierarchy.push_back(Ground);


	//�I�u�W�F�N�g�̕`�揈��
	for (const auto& e : Hierarchy)
	{
		e->Start();
	}
}

void Scene_Game::Update()
{

	if (Input::GetKeyState(KEY_INPUT_ESCAPE) == Input::KEY_DOWN)
	{
		SCENE_MANAGER->LoadScene(EXIT_NUM_SCENE);
		SkyBox->GetComponent<MeshRenderer>()->UnloadAll();
		Cube->GetComponent<MeshRenderer>()->UnloadAll();
		Ground->GetComponent<MeshRenderer>()->UnloadAll();
		return;
	}

	if (Input::GetKeyState(KEY_INPUT_UP) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Translate(0.0f, 0.0f, 0.1f);
	}	
	
	if (Input::GetKeyState(KEY_INPUT_DOWN) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Translate(0.0f, 0.00f, -0.1f);
	}

	if (Input::GetKeyState(KEY_INPUT_RIGHT) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Translate(0.1f, 0.0f, 0.0f);
	}

	if (Input::GetKeyState(KEY_INPUT_LEFT) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Translate(-0.1f, 0.0f, 0.0f);
	}

	if (Input::GetKeyState(KEY_INPUT_SHIFT) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Translate(0.0f, -0.1f, 0.0f);
	}

	if (Input::GetKeyState(KEY_INPUT_SPACE) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Translate(0.0f, 0.1f, 0.0f);
	}

	//�I�u�W�F�N�g�̕`�揈��
	for (const auto& e : Hierarchy)
	{
		e->Update();
	}
}

void Scene_Game::Draw()
{

	//��ʂ�h��Ԃ�
	float color[4] = { COLOR_NORMALIZATION_255(44, 70, 112, 1.0f) };
	D3D->Get_ID3D11DeviceContext()->ClearRenderTargetView(D3D->Get_RenderTargetView(), color);

	//�I�u�W�F�N�g�̕`�揈��
	for (const auto& e : Hierarchy)
	{
		e->Draw();
	}
}