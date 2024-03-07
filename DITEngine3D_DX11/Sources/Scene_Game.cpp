#include "DITEngine3D.h"
#include "Scene_Game.h"
#include "DITEngineSystem.h"

void Scene_Game::Start()
{
	//== 環境画像の設定（ミップレベルごとにロード） ==//

	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_2000x1000.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_2000x1000_blur_1px.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_2000x1000_blur_2px.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_2000x1000_blur_4px.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_2000x1000_blur_8px.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_2000x1000_blur_16px.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_2000x1000_blur_32px.jpg");


	SheetNormalMap = new Texture();
	SheetNormalMap->Create("Asset/model/SheetNormal.jpg");	
	
	RoadNormalMap = new Texture();
	RoadNormalMap->Create("Asset/model/Asphalt_Normal.png");	
	
	TestNoise_MetallicMap = new Texture();
	TestNoise_MetallicMap->Create("Asset/model/TestNoise.jpg");

	
	//== シェーダー設定 ==//

	//頂点シェーダー
	Shader::AddVertexShader("Asset/shader/DirectionalLight_VS.cso", "Directional");
	Shader::AddVertexShader("Asset/shader/unlitTextureVS.cso", "Unlit");
	Shader::AddVertexShader("Asset/shader/UI_BaseShader_VS.cso", "UI_Base");

	//ピクセルシェーダー
	Shader::AddPixelShader("Asset/shader/DisneyBRDF_PS.cso", "Disney");
	Shader::AddPixelShader("Asset/shader/unlitTexturePS.cso", "Unlit");
	Shader::AddPixelShader("Asset/shader/UI_BaseShader_PS.cso", "UI_Base");


	//== ImGUI設定 ==//

	//デバッグウィンドウ
	ig_WorldSettingWindow = new ImGUI_WorldSettingWindow();
	ig_WorldSettingWindow->SetWindowName("DebugWindow");
	ImGUIManager::AddWindow(ig_WorldSettingWindow);

	//マテリアルウィンドウ
	ig_MaterialWindow = new ImGUI_MaterialWindow();
	ig_MaterialWindow->SetWindowName("MaterialWindow");
	ImGUIManager::AddWindow(ig_MaterialWindow);

	
	//== オブジェクト設定 ==//
	
	//== サンライト ==//
	DirectionalLight_Obj = new GameObject();

	DirectionalLight* DirLight_buf = DirectionalLight_Obj->AddComponent<DirectionalLight>();

	Hierarchy.push_back(DirectionalLight_Obj);
	
	//== メインカメラ ==//
	MainCamera = new GameObject();
	
	MainCamera->AddComponent<Camera>();

	MainCamera->transform->position = Vector3(-9.0f, 2.0f, 4.0f);
	MainCamera->transform->rotation = Vector3(0.0f, DirectX::XMConvertToRadians(160.0f), 0.0f);
	
	Hierarchy.push_back(MainCamera);
	
	
	//== スカイボックス ==//
	SkyBox = new GameObject();
	
	SkyBox->AddComponent<MeshRenderer>()->Load("Asset\\model\\SkyBox_Town.obj");
	
	SkyBox->transform->scale = Vector3(30.0f, 30.0f, 30.0f);

	SkyBox->GetComponent<MeshRenderer>()->GetSubset_Index(0)->Material.VertexShader = Shader::GetVertexShader("Unlit");
	SkyBox->GetComponent<MeshRenderer>()->GetSubset_Index(0)->Material.PixelShader = Shader::GetPixelShader("Unlit");

	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(SkyBox->GetComponent<MeshRenderer>());
	
	Hierarchy.push_back(SkyBox);
	

	//== 車体 ==//
	Body = new GameObject();
	
	Body->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Body.obj");

	Body->AddComponent<Spring>()->SetStretchMaxMin(0.2f, 0.0f);

	Body->GetComponent<Spring>()->StretchSpeed = 0.0002f;

	//ノーマルマップ有効
	Body->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Sheet")->Material.Disney_Material.TextureEnable[1] = 1.0f;
	Body->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Sheet")->Material.NormalMap = SheetNormalMap->GetResource();

	
	Hierarchy.push_back(Body);
	
	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(Body->GetComponent<MeshRenderer>());
	
	Body->transform->position.x = -5.0f;
	
	Body->transform->Rotate(0.0f, DirectX::XMConvertToRadians(-90.0f), 0.0f);

	
	
	//== マフラー ==//
	Muffler = new GameObject();
	
	Muffler->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Muffler.obj");
	
	Muffler->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Muffler")->Material.Disney_Material.TextureEnable[2] = 1.0f;
	Muffler->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Muffler")->Material.MetallicMap = TestNoise_MetallicMap->GetResource();

	Muffler->Set_Parent(Body);
	
	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(Muffler->GetComponent<MeshRenderer>());
	
	//== エンジン ==//
	Engine = new GameObject();
	
	Engine->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Engine.obj");
	
	Engine->Set_Parent(Body);
	
	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(Engine->GetComponent<MeshRenderer>());
	
	//== ハンドル ==//
	Handle = new GameObject();
	
	Handle->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Handle.obj");
	
	Handle->Set_Parent(Body);
	
	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(Handle->GetComponent<MeshRenderer>());

	//== サスペンションスプリング ==//

	SuspensionSpring = new GameObject();

	SuspensionSpring->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Cube.obj");

	SuspensionSpring->GetComponent<MeshRenderer>()->Enable = false;

	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(SuspensionSpring->GetComponent<MeshRenderer>());

	SuspensionSpring->transform->position = Vector3(0.0f, 1.054f, 1.706f);
	SuspensionSpring->transform->rotation = Vector3(-0.44f, 0.0f, 0.0f);

	SuspensionSpring->AddComponent<Spring>()->SetStretchMaxMin(0.2f, 0.0f);

	SuspensionSpring->Set_Parent(Body);
	
	//== フロントフェンダー ==//
	FrontFender = new GameObject();
	
	FrontFender->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_FrontFender.obj");

	FrontFender->Set_Parent(SuspensionSpring);
	
	FrontFender->transform->position = Vector3(0.0f, -0.2f, -2.006f);
	FrontFender->transform->rotation = Vector3(0.452f, 0.0f, 0.0f);

	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(FrontFender->GetComponent<MeshRenderer>());
	
	//== フロントタイヤ ==//
	FrontTire = new GameObject();
	
	FrontTire->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_FrontTire.obj");
	
	FrontTire->Set_Parent(FrontFender);
	
	FrontTire->transform->position = Vector3(0.0f, 0.813f, 1.832f);
	
	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(FrontTire->GetComponent<MeshRenderer>());
	
	//== リアタイヤ ==//
	RearTire = new GameObject();
	
	RearTire->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_RearTire.obj");
	
	RearTire->Set_Parent(Body);
	
	RearTire->transform->position = Vector3(0.0f, 0.813f, -2.069f);
	
	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(RearTire->GetComponent<MeshRenderer>());
	
	
	//== テストスフィア ==//
	Sphere = new GameObject();
	
	Sphere->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Sphere.obj");
	
	Sphere->transform->position.x = 4.0f;
	Sphere->transform->position.y = 1.0f;

	Sphere->GetComponent<MeshRenderer>()->GetSubset_Index(0)->Material.Disney_Material.TextureEnable[2] = 1.0f;
	Sphere->GetComponent<MeshRenderer>()->GetSubset_Index(0)->Material.MetallicMap = TestNoise_MetallicMap->GetResource();

	
	Hierarchy.push_back(Sphere);
	
	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(Sphere->GetComponent<MeshRenderer>());

	
	//== スタジオ（Bypass） ==//

	//５つのステージをループ
	for (int i = 0; i < 5; i++)
	{
		Studio_Bypass[i] = new GameObject();

		MeshRenderer* Studio_Bypass_MeshRenderer = Studio_Bypass[i]->AddComponent<MeshRenderer>();
		
		Studio_Bypass_MeshRenderer->Load("Asset\\model\\Studio_Bypass.obj");

		//ノーマルマップ有効
		Studio_Bypass_MeshRenderer->GetSubset_MaterialName("Road")->Material.Disney_Material.TextureEnable[1] = 1.0f;
		Studio_Bypass_MeshRenderer->GetSubset_MaterialName("Road")->Material.NormalMap = RoadNormalMap->GetResource();

		Studio_Bypass_MeshRenderer->GetSubset_MaterialName("WalkRoad")->Material.Disney_Material.TextureEnable[1] = 1.0f;
		Studio_Bypass_MeshRenderer->GetSubset_MaterialName("WalkRoad")->Material.NormalMap = RoadNormalMap->GetResource();


		Hierarchy.push_back(Studio_Bypass[i]);

		Studio_Bypass[i]->transform->position.x -= 56.0f * i;

		Studio_Bypass[i]->transform->position.z += 4.0f;

		ig_MaterialWindow->AddMaterialEditor_MeshRenderer(Studio_Bypass_MeshRenderer);
	}


	float a = sinf(DirectX::XMConvertToRadians(180.0f));


	//== テストUI ==//
	TestUI = new GameObject();

	UISpriteRenderer* uis_buf = TestUI->AddComponent<UISpriteRenderer>();
	 
	Texture* TestUITexture;
	TestUITexture = new Texture();
	TestUITexture->Create("Asset/texture/CB400SF_Logo.png");
	ID3D11ShaderResourceView* TestUI_buf = TestUITexture->GetResource();

	uis_buf->SetTexture(TestUI_buf);
	uis_buf->SetVertexShader(Shader::GetVertexShader("UI_Base"), Shader::GetInputLayout("UI_Base"));
	uis_buf->SetPixelShader(Shader::GetPixelShader("UI_Base"));

	//デバッグウィンドウの初期化
	ig_WorldSettingWindow->UI_Position_X_Slider = TestUI->transform->position.x;
	ig_WorldSettingWindow->UI_Position_Y_Slider = TestUI->transform->position.y;

	ig_WorldSettingWindow->UI_Rotation_Slider = TestUI->transform->rotation.z;

	ig_WorldSettingWindow->UI_Scale_X_Slider = TestUI->transform->scale.x;
	ig_WorldSettingWindow->UI_Scale_Y_Slider = TestUI->transform->scale.y;

	Hierarchy.push_back(TestUI);

	
	//マテリアルデータ読み込み処理
	ig_MaterialWindow->Init();

	//デバッグデータ読み込み処理
	ig_WorldSettingWindow->Init();

	

	//オブジェクトの描画処理
	for (const auto& e : Hierarchy)
	{
		e->Start();
	}
}

void Scene_Game::Update()
{
	//== 終了処理 ==//
	if (Input::GetKeyState(KEY_INPUT_ESCAPE) == Input::KEY_DOWN)
	{
		SCENE_MANAGER->LoadScene(EXIT_NUM_SCENE);
		return;
	}


	float BikeSpeed = 200.0f;


	//エンジンとマフラーの振動
	double Vib = Time::GetWorldTime().MMSecond;

	Engine->transform->position.y = sin(Vib) * 0.002;
	Muffler->transform->position.y = sin(Vib) * 0.003;

	//タイヤの回転
	FrontTire->transform->Rotate(0.002f * BikeSpeed, 0.0f, 0.0f);
	RearTire->transform->Rotate(0.002f * BikeSpeed, 0.0f, 0.0f);

	//== カメラの操作 ==//
	MainCamera->transform->Translate(
		Input::GetGamePad_LeftStick().x * 0.0000001f * Time::GetDeltaTime(),
		0.0f,
		Input::GetGamePad_LeftStick().y * 0.0000001f * Time::GetDeltaTime()
	);
	
	MainCamera->transform->Rotate(
		-Input::GetGamePad_RightStick().y * 0.0000001f * Time::GetDeltaTime(),
		Input::GetGamePad_RightStick().x * 0.0000001f * Time::GetDeltaTime(),
		0.0f
	);

	//if (Input::GetKeyState(KEY_INPUT_W) == Input::KEY_WHILE_DOWN)
	//{
	//	MainCamera->transform->Translate(0.0f, 0.0f, 0.005f * Time::GetDeltaTime());
	//}	
	//
	//if (Input::GetKeyState(KEY_INPUT_S) == Input::KEY_WHILE_DOWN)
	//{
	//	MainCamera->transform->Translate(0.0f, 0.0f, -0.005f * Time::GetDeltaTime());
	//}
	//
	//if (Input::GetKeyState(KEY_INPUT_D) == Input::KEY_WHILE_DOWN)
	//{
	//	MainCamera->transform->Translate(0.005f * Time::GetDeltaTime(), 0.0f, 0.0f);
	//}
	//
	//if (Input::GetKeyState(KEY_INPUT_A) == Input::KEY_WHILE_DOWN)
	//{
	//	MainCamera->transform->Translate(-0.005f * Time::GetDeltaTime(), 0.0f, 0.0f);
	//}
	//
	//
	//
	//if (Input::GetKeyState(KEY_INPUT_UP) == Input::KEY_WHILE_DOWN)
	//{
	//	MainCamera->transform->Rotate(-0.0005f * Time::GetDeltaTime(), 0.0f, 0.0f);
	//}
	//
	//if (Input::GetKeyState(KEY_INPUT_DOWN) == Input::KEY_WHILE_DOWN)
	//{
	//	MainCamera->transform->Rotate(0.0005f * Time::GetDeltaTime(), 0.0f, 0.0f);
	//}
	//
	//if (Input::GetKeyState(KEY_INPUT_RIGHT) == Input::KEY_WHILE_DOWN)
	//{
	//	MainCamera->transform->Rotate(0.0f, 0.001f * Time::GetDeltaTime(), 0.0f);
	//}
	//
	//if (Input::GetKeyState(KEY_INPUT_LEFT) == Input::KEY_WHILE_DOWN)
	//{
	//	MainCamera->transform->Rotate(0.0f, -0.001f * Time::GetDeltaTime(), 0.0f);
	//}



	Body->transform->Translate(0.0f, sin(Time::GetWorldTime().Get_Second_Float() * 10.0f) * 0.0005f, 0.0f);
	FrontFender->transform->position.y += cos(Time::GetWorldTime().Get_Second_Float() * 10.0f) * 0.0005f;
	RearTire->transform->position.y += cos(Time::GetWorldTime().Get_Second_Float() * 10.0f) * 0.0005f;

	//車体の揺れ
	if (rand() % 40 == 0)
	{
		Body->GetComponent<Spring>()->SetStretch((rand() % 2) * 0.01f);
	}
	
	//フロントフェンダーの揺れ
	if (rand() % 20 == 0)
	{
		SuspensionSpring->GetComponent<Spring>()->SetStretch((rand() % 2) * 0.01f);
	}

	for (int i = 0; i < 5; i++)
	{
		Studio_Bypass[i]->transform->Translate(0.001f * BikeSpeed, 0.0f, 0.0f);

		if (Studio_Bypass[i]->transform->position.x >= 84.0f)
		{
			Studio_Bypass[i]->transform->position.x -= 224.0f;
		}
	}


	//== デバッグウィンドウの値を設定 ==//

	//FPS表示
	ig_WorldSettingWindow->FPS = Time::Get_FPS();
	//時間表示
	ig_WorldSettingWindow->GameTime = Time::GetWorldTime();


	//座標
	TestUI->transform->position.x = ig_WorldSettingWindow->UI_Position_X_Slider;
	TestUI->transform->position.y = ig_WorldSettingWindow->UI_Position_Y_Slider;

	//回転
	TestUI->transform->rotation.z = DirectX::XMConvertToRadians(ig_WorldSettingWindow->UI_Rotation_Slider);

	//スケール
	TestUI->transform->scale.x = ig_WorldSettingWindow->UI_Scale_X_Slider;
	TestUI->transform->scale.y = ig_WorldSettingWindow->UI_Scale_Y_Slider;

	//FrontFender->transform->position = ig_DebugWindow->CubePosition;
	//FrontFender->transform->rotation = ig_DebugWindow->CubeRotation;
	//FrontFender->transform->scale = ig_DebugWindow->CubeScale;


	//DirectionalLight
	DirectionalLight* DirLight_buf = DirectionalLight_Obj->GetComponent<DirectionalLight>();

	DirLight_buf->SetLightColor(ig_WorldSettingWindow->Light_Diffuse);
	DirLight_buf->SetAmbient(ig_WorldSettingWindow->Light_Ambient);
	DirLight_buf->SetDirection(ig_WorldSettingWindow->Light_Direction);
	DirLight_buf->SetIntensity(ig_WorldSettingWindow->Light_Intensity);


	//== バイブレーションテスト ==//

	//バイブレーションテスト
	if (Input::GetGamePadButtonState(GAMEPAD_INPUT_B) == Input::KEY_DOWN)
	{
		Input::SetGamePadVibration(1.0f, 0.25f);
	}


	//オブジェクトの描画処理
	for (const auto& e : Hierarchy)
	{
		e->Update();
	}
}

void Scene_Game::Draw()
{

	//== 画面を塗りつぶす ==//
	float color[4] = { COLOR_NORMALIZATION_255(44, 70, 112, 1.0f) };
	D3D->Get_ID3D11DeviceContext()->ClearRenderTargetView(D3D->Get_RenderTargetView(), color);


	//== 視点の情報をシェーダーに送る ==//
	EYE_INFO eye_info;
	
	//メインカメラの座標
	eye_info.EyePosition = DirectX::SimpleMath::Vector4
	(
		MainCamera->transform->position.x,
		MainCamera->transform->position.y,
		MainCamera->transform->position.z,
		0.0f
	);

	eye_info.DistanceFog_Color = ig_WorldSettingWindow->DistanceFog_Color.simpleMath_vector4;

	eye_info.DistanceFog_Distance.x = ig_WorldSettingWindow->DistanceFog_Distance;

	D3D->SetEyeInfo(eye_info);


	//オブジェクトの描画処理
	for (const auto& e : Hierarchy)
	{
		e->Draw();
	}
}

void Scene_Game::Release()
{
	//テクスチャ解放
	delete SheetNormalMap;
	delete RoadNormalMap;
	delete TestNoise_MetallicMap;
}