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
	
	
	//== シェーダー設定 ==//

	//頂点シェーダー
	Shader::AddVertexShader("Asset/shader/PointLight_VS.cso", "PointLight");

	//ピクセルシェーダー
	Shader::AddPixelShader("Asset/shader/PointLight_PS.cso", "PointLight");
	Shader::AddPixelShader("Asset/shader/SpecularReflection_PS.cso", "Specular");

	
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
	
	MeshRenderer*  meshRenderer_buf = SkyBox->AddComponent<MeshRenderer>();

	meshRenderer_buf->Load("Asset\\model\\SkyBox_Town.obj");
	
	SkyBox->transform->scale = Vector3(30.0f, 30.0f, 30.0f);
	
	//SkyBox->transform->Rotate(0.0f, 90.0f, 0.0f);

	Hierarchy.push_back(SkyBox);
	
	
	//== マフラー ==//
	Muffler = new GameObject();
	
	meshRenderer_buf = Muffler->AddComponent<MeshRenderer>();
	
	meshRenderer_buf->Load("Asset\\model\\CB400SF\\CB400SF_Muffler.obj");
	
	Hierarchy.push_back(Muffler);
	
	Muffler->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== エンジン・トランスミッション ==//
	Engine_Transmission = new GameObject();
	
	Engine_Transmission->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Engine.obj");
	
	Hierarchy.push_back(Engine_Transmission);
	
	Engine_Transmission->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== タンク ==//
	Tank = new GameObject();
	
	Tank->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Body.obj");
	
	Hierarchy.push_back(Tank);
	
	Tank->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== フレーム ==//
	Frame = new GameObject();
	
	Frame->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Frame.obj");
	
	Hierarchy.push_back(Frame);
	
	Frame->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== リアフェンダー・カバー類 ==//
	RearFender_Cover = new GameObject();
	
	RearFender_Cover->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_RearFender_Cover.obj");
	
	Hierarchy.push_back(RearFender_Cover);
	
	RearFender_Cover->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== サスペンション周り ==//
	Suspension = new GameObject();
	
	Suspension->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Suspension.obj");
	
	Hierarchy.push_back(Suspension);
	
	Suspension->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== キャブレーター ==//
	Carburetor = new GameObject();
	
	Carburetor->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Carburetor.obj");
	
	Hierarchy.push_back(Carburetor);
	
	Carburetor->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== ラジエーター ==//
	Radiator = new GameObject();
	
	Radiator->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Radiator.obj");
	
	Hierarchy.push_back(Radiator);

	Radiator->GetComponent<MeshRenderer>()->GetSubset(2)->Material.PixelShader = Shader::GetPixelShader("Specular");
	
	Radiator->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== アクスル周り ==//
	RearAxle = new GameObject();
	
	RearAxle->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_RearAxle.obj");
	
	Hierarchy.push_back(RearAxle);
	
	RearAxle->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== リアサスペンション ==//
	RearSuspension = new GameObject();
	
	RearSuspension->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_RearSuspension.obj");

	Hierarchy.push_back(RearSuspension);
	
	RearSuspension->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== タイヤ ==//
	Tire = new GameObject();
	
	Tire->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Tire.obj");

	Hierarchy.push_back(Tire);
	
	Tire->transform->scale = Vector3(0.03f, 0.03f, 0.03f);	
	
	
	//== ホイール ==//
	Wheel = new GameObject();
	
	Wheel->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Wheel.obj");

	Hierarchy.push_back(Wheel);
	
	Wheel->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	
	//== シート ==//
	Seat = new GameObject();
	
	Seat->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Seat.obj");
	
	Hierarchy.push_back(Seat);
	
	Seat->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== メーター ==//
	Metor = new GameObject();
	
	Metor->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Metor.obj");
	
	Hierarchy.push_back(Metor);
	
	Metor->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== メーター背景 ==//
	Metor_BackGround = new GameObject();
	
	Metor_BackGround->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Metor_BackGround.obj");
	
	Hierarchy.push_back(Metor_BackGround);
	
	Metor_BackGround->transform->scale = Vector3(0.03f, 0.03f, 0.03f);
	
	
	//== Sphere ==//
	Sphere = new GameObject();
	
    Sphere->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Sphere.obj");
	
	Hierarchy.push_back(Sphere);
	
	Sphere->transform->position.x -= 5.0f;
	Sphere->transform->position.y += 1.0f;
	
	//== 地面 ==//
	Ground = new GameObject();
	
	Ground->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Ground.obj");
	
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