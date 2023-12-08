#include "DITEngine3D.h"
#include "Scene_Game.h"

void Scene_Game::Start()
{
	//���摜�̐ݒ�
	Texture* CubeMap;
	CubeMap = new Texture();
	CubeMap->Create("Asset/texture/parking_garage_2000_1000.jpg");
	
	ID3D11ShaderResourceView* CubeMap_buf = CubeMap->GetResource();
	
	D3D->Get_ID3D11DeviceContext()->PSSetShaderResources(0, 1, &CubeMap_buf);
	
	
	//�V�F�[�_�[�ݒ�
	Shader::AddShader("Asset/shader/unlitTextureVS.cso", "Asset/shader/unlitTexturePS.cso", "Unlit");
	Shader::AddShader("Asset/shader/vertexLightingVS.cso", "Asset/shader/vertexLightingPS.cso", "Light");
	Shader::AddShader("Asset/shader/PointLight_VS.cso", "Asset/shader/PointLight_PS.cso", "PointLight");
	Shader::AddShader("Asset/shader/PointLight_VS.cso", "Asset/shader/SpecularReflection_PS.cso", "SpecularReflection");
	
	
	//�I�u�W�F�N�g�ݒ�
	
	//== �|�C���g���C�g ==//
	PointLight_Obj = new GameObject();
	
	PointLight* pointLightBuf = PointLight_Obj->AddComponent<PointLight>();
	
	pointLightBuf->SetAttenuation(1.0f, 0.0f, 0.0f);
	pointLightBuf->SetLightColor(1.0f, 1.0f, 1.0f, 10.0f);
	
	Hierarchy.push_back(PointLight_Obj);
	
	PointLight_Obj->transform->position = Vector3(-2.0f, 3.0f, 1.0f);
	
	//== ���C���J���� ==//
	MainCamera = new GameObject();
	
	MainCamera->AddComponent<Camera>();
	
	Hierarchy.push_back(MainCamera);
	
	
	//== ���C�g�J���� ==//
	LightCamera = new GameObject();
	
	LightCamera->AddComponent<Camera>();
	
	Hierarchy.push_back(LightCamera);
	
	LightCamera->transform->position = Vector3(-13.0f, 5.0f, -13.0f);
	LightCamera->transform->Rotate(0.0f, 45.0f, 0.0f);
	
	
	////== �e�X�gBOX ==//
	SkyBox = new GameObject();
	
	SkyBox->AddComponent<MeshRenderer>()->Load("Asset\\model\\SkyBox_Town.obj", "Unlit");
	
	SkyBox->transform->scale = Vector3(30.0f, 30.0f, 30.0f);
	
	Hierarchy.push_back(SkyBox);
	
	
	//== �L���[�u ==//
	Cube = new GameObject();
	
	Cube->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF_Muffler.obj", "SpecularReflection");
	
	Hierarchy.push_back(Cube);
	
	Cube->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	//Cube->transform->position.y = 1.0f;
	Cube->transform->position.x += 2.0f;
	
	
	//== �L���[�u_�q�I�u�W�F�N�g ==//
	Cube_Child = new GameObject();
	
	Cube_Child->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Cube.obj", "SpecularReflection");
	
	Hierarchy.push_back(Cube_Child);
	
	Cube_Child->transform->position.y = -0.2f;
	Cube_Child->transform->position.z = 0.5f;
	Cube_Child->transform->position.x = 0.2f;
	Cube_Child->transform->scale = Vector3(0.02f, 0.02f, 1.0f);
	
	Cube_Child->Set_Parent(MainCamera);
	
	
	//== �X�t�B�A ==//
	
	Sphere = new GameObject();
	
	Sphere->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Sphere.obj", "SpecularReflection");
	
	Hierarchy.push_back(Sphere);
	
	Sphere->transform->position.y += 1.0f;
	Sphere->transform->position.x -= 2.0f;
	
	//== �n�� ==//
	Ground = new GameObject();
	
	Ground->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Ground.obj", "PointLight");
	
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
		Cube_Child->GetComponent<MeshRenderer>()->UnloadAll();
		Ground->GetComponent<MeshRenderer>()->UnloadAll();
		return;
	}

	if (Input::GetKeyState(KEY_INPUT_L) == Input::KEY_WHILE_DOWN)
	{
		if (Input::GetKeyState(KEY_INPUT_W) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->Translate(0.0f, 0.0f, 0.03f);
		}

		if (Input::GetKeyState(KEY_INPUT_S) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->Translate(0.0f, 0.00f, -0.03f);
		}

		if (Input::GetKeyState(KEY_INPUT_D) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->Translate(0.03f, 0.0f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_A) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->Translate(-0.03f, 0.0f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_SHIFT) == Input::KEY_WHILE_DOWN)
		{
			Cube->transform->Translate(0.0f, -0.1f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_SPACE) == Input::KEY_WHILE_DOWN)
		{
			Cube->transform->Translate(0.0f, 0.1f, 0.0f);
		}
	}
	else
	{
		if (Input::GetKeyState(KEY_INPUT_W) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->Translate(0.0f, 0.0f, 0.03f);
		}

		if (Input::GetKeyState(KEY_INPUT_S) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->Translate(0.0f, 0.00f, -0.03f);
		}

		if (Input::GetKeyState(KEY_INPUT_D) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->Translate(0.03f, 0.0f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_A) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->Translate(-0.03f, 0.0f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_SHIFT) == Input::KEY_WHILE_DOWN)
		{
			Cube->transform->Translate(0.0f, -0.1f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_SPACE) == Input::KEY_WHILE_DOWN)
		{
			Cube->transform->Translate(0.0f, 0.1f, 0.0f);
		}
	}


	if (Input::GetKeyState(KEY_INPUT_RETURN) == Input::KEY_WHILE_DOWN)
	{
		LightCamera->GetComponent<Camera>()->Enable = true;
		MainCamera->GetComponent<Camera>()->Enable = false;
	}
	else
	{
		LightCamera->GetComponent<Camera>()->Enable = false;
		MainCamera->GetComponent<Camera>()->Enable = true;
	}

	if (Input::GetKeyState(KEY_INPUT_RIGHT) == Input::KEY_WHILE_DOWN) 
	{
		MainCamera->transform->Rotate(0.0f, 0.01f, 0.0f);
	}

	if (Input::GetKeyState(KEY_INPUT_LEFT) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Rotate(0.0f, -0.01f, 0.0f);
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


	//���_�̏����V�F�[�_�[�ɑ���
	EYE_INFO eye_info;
	
	//���C���J�����̍��W
	eye_info.EyePosition = DirectX::SimpleMath::Vector4
	(
		MainCamera->transform->position.x,
		MainCamera->transform->position.y,
		MainCamera->transform->position.z,
		0.0f
	);

	D3D->SetEyeInfo(eye_info);


	//�I�u�W�F�N�g�̕`�揈��
	for (const auto& e : Hierarchy)
	{
		e->Draw();
	}
}