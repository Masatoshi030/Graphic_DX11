#include "DITEngine3D.h"
#include "Scene_Game.h"

void Scene_Game::Start()
{
	//環境画像の設定
	Texture* CubeMap;
	CubeMap = new Texture();
	CubeMap->Create("Asset/texture/parking_garage_2000_1000.jpg");
	
	ID3D11ShaderResourceView* CubeMap_buf = CubeMap->GetResource();
	
	D3D->Get_ID3D11DeviceContext()->PSSetShaderResources(0, 1, &CubeMap_buf);
	
	
	//シェーダー設定
	Shader::AddShader("Asset/shader/unlitTextureVS.cso", "Asset/shader/unlitTexturePS.cso", "Unlit");
	Shader::AddShader("Asset/shader/vertexLightingVS.cso", "Asset/shader/vertexLightingPS.cso", "Light");
	Shader::AddShader("Asset/shader/PointLight_VS.cso", "Asset/shader/PointLight_PS.cso", "PointLight");
	Shader::AddShader("Asset/shader/PointLight_VS.cso", "Asset/shader/SpecularReflection_PS.cso", "SpecularReflection");
	
	
	//オブジェクト設定
	
	//== ポイントライト ==//
	PointLight_Obj = new GameObject();
	
	PointLight* pointLightBuf = PointLight_Obj->AddComponent<PointLight>();
	
	pointLightBuf->SetAttenuation(1.0f, 0.0f, 0.0f);
	pointLightBuf->SetLightColor(1.0f, 0.976431f, 0.8f, 10.0f);
	
	Hierarchy.push_back(PointLight_Obj);
	
	PointLight_Obj->transform->position = Vector3(2.0f, 4.0f, 1.0f);
	
	//== メインカメラ ==//
	MainCamera = new GameObject();
	
	MainCamera->AddComponent<Camera>();
	
	Hierarchy.push_back(MainCamera);
	
	
	//== ライトカメラ ==//
	LightCamera = new GameObject();
	
	LightCamera->AddComponent<Camera>();
	
	Hierarchy.push_back(LightCamera);
	
	LightCamera->transform->position = Vector3(-13.0f, 5.0f, -13.0f);
	LightCamera->transform->Rotate(0.0f, 45.0f, 0.0f);
	
	
	//== スカイボックス ==//
	SkyBox = new GameObject();
	
	SkyBox->AddComponent<MeshRenderer>()->Load("Asset\\model\\SkyBox_Town.obj", "Unlit");
	
	SkyBox->transform->scale = Vector3(30.0f, 30.0f, 30.0f);
	
	//SkyBox->transform->Rotate(0.0f, 90.0f, 0.0f);

	Hierarchy.push_back(SkyBox);
	
	
	//== マフラー ==//
	Muffler = new GameObject();
	
	MeshRenderer* meshRenderer_buf = Muffler->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Muffler.obj", "SpecularReflection");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 1.0f;
	}
	
	Hierarchy.push_back(Muffler);
	
	Muffler->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== エンジン・トランスミッション ==//
	Engine_Transmission = new GameObject();
	
	meshRenderer_buf = Engine_Transmission->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Engine.obj", "SpecularReflection");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.8f;
	}
	
	Hierarchy.push_back(Engine_Transmission);
	
	Engine_Transmission->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== タンク ==//
	Tank = new GameObject();
	
	meshRenderer_buf = Tank->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Body.obj", "SpecularReflection");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.8f;
	}
	
	Hierarchy.push_back(Tank);
	
	Tank->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== フレーム ==//
	Frame = new GameObject();
	
	meshRenderer_buf = Frame->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Frame.obj", "SpecularReflection");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.3f;
	}
	
	Hierarchy.push_back(Frame);
	
	Frame->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== リアフェンダー・カバー類 ==//
	RearFender_Cover = new GameObject();
	
	meshRenderer_buf = RearFender_Cover->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_RearFender_Cover.obj", "PointLight");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}
	
	Hierarchy.push_back(RearFender_Cover);
	
	RearFender_Cover->transform->scale = Vector3(0.03f, 0.03f, 0.03f);


	//== サスペンション周り ==//
	Suspension = new GameObject();

	meshRenderer_buf = Suspension->AddComponent<MeshRenderer>();

	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Suspension.obj", "SpecularReflection");

	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}

	Hierarchy.push_back(Suspension);

	Suspension->transform->scale = Vector3(0.03f, 0.03f, 0.03f);


	//== キャブレーター ==//
	Carburetor = new GameObject();

	meshRenderer_buf = Carburetor->AddComponent<MeshRenderer>();

	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Carburetor.obj", "SpecularReflection");

	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}

	Hierarchy.push_back(Carburetor);

	Carburetor->transform->scale = Vector3(0.03f, 0.03f, 0.03f);


	//== ラジエーター ==//
	Radiator = new GameObject();

	meshRenderer_buf = Radiator->AddComponent<MeshRenderer>();

	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Radiator.obj", "SpecularReflection");

	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}

	Hierarchy.push_back(Radiator);

	Radiator->transform->scale = Vector3(0.03f, 0.03f, 0.03f);


	//== アクスル周り ==//
	RearAxle = new GameObject();
	
	meshRenderer_buf = RearAxle->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_RearAxle.obj", "SpecularReflection");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}
	
	Hierarchy.push_back(RearAxle);
	
	RearAxle->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== リアサスペンション ==//
	RearSuspension = new GameObject();
	
	meshRenderer_buf = RearSuspension->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_RearSuspension.obj", "SpecularReflection");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}
	
	Hierarchy.push_back(RearSuspension);
	
	RearSuspension->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== タイヤ ==//
	Tire = new GameObject();
	
	meshRenderer_buf = Tire->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Tire.obj", "PointLight");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}
	
	Hierarchy.push_back(Tire);
	
	Tire->transform->scale = Vector3(0.03f, 0.03f, 0.03f);	


	//== ホイール ==//
	Wheel = new GameObject();
	
	meshRenderer_buf = Wheel->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Wheel.obj", "SpecularReflection");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}
	
	Hierarchy.push_back(Wheel);
	
	Wheel->transform->scale = Vector3(0.03f, 0.03f, 0.03f);



	//== シート ==//
	Seat = new GameObject();

	meshRenderer_buf = Seat->AddComponent<MeshRenderer>();

	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Seat.obj", "PointLight");

	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}

	Hierarchy.push_back(Seat);

	Seat->transform->scale = Vector3(0.03f, 0.03f, 0.03f);


	//== メーター ==//
	Metor = new GameObject();

	meshRenderer_buf = Metor->AddComponent<MeshRenderer>();

	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Metor.obj", "SpecularReflection");

	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}

	Hierarchy.push_back(Metor);

	Metor->transform->scale = Vector3(0.03f, 0.03f, 0.03f);


	//== メーター背景 ==//
	Metor_BackGround = new GameObject();

	meshRenderer_buf = Metor_BackGround->AddComponent<MeshRenderer>();

	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Metor_BackGround.obj", "PointLight");

	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.5f;
	}

	Hierarchy.push_back(Metor_BackGround);

	Metor_BackGround->transform->scale = Vector3(0.03f, 0.03f, 0.03f);


	//== Sphere ==//
	Sphere = new GameObject();
	
	meshRenderer_buf = Sphere->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\BaseModel\\Sphere.obj", "SpecularReflection");
	
	for (int i = 0; i < meshRenderer_buf->GetModel()->SubsetNum; i++)
	{
		meshRenderer_buf->GetSubset(i)->Material.Material.Metalic_.x = 0.9f;
	}
	
	Hierarchy.push_back(Sphere);
	
	Sphere->transform->position.x -= 5.0f;
	Sphere->transform->position.y += 1.0f;

	//== 地面 ==//
	Ground = new GameObject();
	
	Ground->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Ground.obj", "PointLight");
	
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
		Muffler->GetComponent<MeshRenderer>()->UnloadAll();
		Engine_Transmission->GetComponent<MeshRenderer>()->UnloadAll();
		Frame->GetComponent<MeshRenderer>()->UnloadAll();
		Ground->GetComponent<MeshRenderer>()->UnloadAll();
		return;
	}

	if (Input::GetKeyState(KEY_INPUT_L) == Input::KEY_WHILE_DOWN)
	{
		if (Input::GetKeyState(KEY_INPUT_W) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->Translate(0.0f, 0.0f, 0.003f * Time::GetDeltaTime());
		}

		if (Input::GetKeyState(KEY_INPUT_S) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->Translate(0.0f, 0.00f, -0.003f * Time::GetDeltaTime());
		}

		if (Input::GetKeyState(KEY_INPUT_D) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->Translate(0.003f * Time::GetDeltaTime(), 0.0f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_A) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->Translate(-0.003f * Time::GetDeltaTime(), 0.0f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_SHIFT) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->position.y -= 0.003f * Time::GetDeltaTime();
		}

		if (Input::GetKeyState(KEY_INPUT_SPACE) == Input::KEY_WHILE_DOWN)
		{
			PointLight_Obj->transform->position.y += 0.003f * Time::GetDeltaTime();
		}
	}
	else
	{
		if (Input::GetKeyState(KEY_INPUT_W) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->Translate(0.0f, 0.0f, 0.003f * Time::GetDeltaTime());
		}

		if (Input::GetKeyState(KEY_INPUT_S) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->Translate(0.0f, 0.00f, -0.003f * Time::GetDeltaTime());
		}

		if (Input::GetKeyState(KEY_INPUT_D) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->Translate(0.003f * Time::GetDeltaTime(), 0.0f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_A) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->Translate(-0.003f * Time::GetDeltaTime(), 0.0f, 0.0f);
		}

		if (Input::GetKeyState(KEY_INPUT_SHIFT) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->position.y -= 0.003f * Time::GetDeltaTime();
		}

		if (Input::GetKeyState(KEY_INPUT_SPACE) == Input::KEY_WHILE_DOWN)
		{
			MainCamera->transform->position.y += 0.003f * Time::GetDeltaTime();
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
		MainCamera->transform->Rotate(0.0f, 0.001f * Time::GetDeltaTime(), 0.0f);
	}

	if (Input::GetKeyState(KEY_INPUT_LEFT) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Rotate(0.0f, -0.001f * Time::GetDeltaTime(), 0.0f);
	}

	if (Input::GetKeyState(KEY_INPUT_DOWN) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Rotate(0.001f * Time::GetDeltaTime(), 0.0f, 0.0f);
	}

	if (Input::GetKeyState(KEY_INPUT_UP) == Input::KEY_WHILE_DOWN)
	{
		MainCamera->transform->Rotate(-0.001f * Time::GetDeltaTime(), 0.0f, 0.0f);
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


	//視点の情報をシェーダーに送る
	EYE_INFO eye_info;
	
	//メインカメラの座標
	eye_info.EyePosition = DirectX::SimpleMath::Vector4
	(
		MainCamera->transform->position.x,
		MainCamera->transform->position.y,
		MainCamera->transform->position.z,
		0.0f
	);

	D3D->SetEyeInfo(eye_info);


	//オブジェクトの描画処理
	for (const auto& e : Hierarchy)
	{
		e->Draw();
	}
}