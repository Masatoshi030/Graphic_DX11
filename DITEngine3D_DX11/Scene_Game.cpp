#include "DITEngine3D.h"
#include "Scene_Game.h"

void Scene_Game::Start()
{
	//シェーダー設定
	Shader::AddShader("Asset/shader/unlitTextureVS.cso", "Asset/shader/unlitTexturePS.cso", "Unlit");
	Shader::AddShader("Asset/shader/vertexLightingVS.cso", "Asset/shader/vertexLightingPS.cso", "Light");


	//オブジェクト設定

	//== メインカメラ ==//
	MainCamera = new GameObject();

	MainCamera->AddComponent<Camera>();

	Hierarchy.push_back(MainCamera);


	//== ライトカメラ ==//
	LightCamera = new GameObject();

	LightCamera->AddComponent<Camera>();

	Hierarchy.push_back(LightCamera);

	LightCamera->transform->position = Vector3(0.0f, 3.0f, -3.0f);


	//== テストBOX ==//
	SkyBox = new GameObject();

	SkyBox->AddComponent<MeshRenderer>()->Load("Asset\\model\\SkyBox_Town.obj", "Unlit");

	SkyBox->transform->scale = Vector3(30.0f, 30.0f, 30.0f);

	Hierarchy.push_back(SkyBox);


	//== キューブ ==//
	Cube = new GameObject();

	Cube->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Cube.obj", "Light");

	Hierarchy.push_back(Cube);

	Cube->transform->position.y = 1.0f;


	//== 地面 ==//
	Ground = new GameObject();

	Ground->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Ground.obj", "Light");

	Hierarchy.push_back(Ground);


	//オブジェクトの描画処理
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
		MainCamera->transform->Translate(0.0f, -0.1f, 0.0f);
	}

	if (Input::GetKeyState(KEY_INPUT_SPACE) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Translate(0.0f, 0.1f, 0.0f);
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

	//オブジェクトの描画処理
	for (const auto& e : Hierarchy)
	{
		e->Update();
	}
}

void Scene_Game::Draw()
{

	//画面を塗りつぶす
	float color[4] = { COLOR_NORMALIZATION_255(44, 70, 112, 1.0f) };
	D3D->Get_ID3D11DeviceContext()->ClearRenderTargetView(D3D->Get_RenderTargetView(), color);

	//オブジェクトの描画処理
	for (const auto& e : Hierarchy)
	{
		e->Draw();
	}
}