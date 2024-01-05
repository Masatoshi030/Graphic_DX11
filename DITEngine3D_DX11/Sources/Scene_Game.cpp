#include "DITEngine3D.h"
#include "Scene_Game.h"

void Scene_Game::Start()
{
	//== 環境画像の設定 ==//
	Texture* CubeMap;
	CubeMap = new Texture();
	CubeMap->Create("Asset/texture/parking_garage_2000x1000.jpg");
	
	ID3D11ShaderResourceView* CubeMap_buf = CubeMap->GetResource();
	
	//画像をセット
	D3D->Get_ID3D11DeviceContext()->PSSetShaderResources(0, 1, &CubeMap_buf);

	//画像の情報を設定
	ENVIRONMENTMAP_INFO em_buf;
	em_buf.ImageSize.x = CubeMap->GetWidth();	//画像の解像度
	em_buf.ImageSize.y = CubeMap->GetHeight();
	
	//画像の情報をセット
	D3D->SetEnvironmentMapInfo(em_buf);

	
	//== シェーダー設定 ==//

	//頂点シェーダー
	Shader::AddVertexShader("Asset/shader/PointLight_VS.cso", "PointLight");
	Shader::AddVertexShader("Asset/shader/unlitTextureVS.cso", "Unlit");
	Shader::AddVertexShader("Asset/shader/UI_BaseShader_VS.cso", "UI_Base");

	//ピクセルシェーダー
	Shader::AddPixelShader("Asset/shader/PointLight_PS.cso", "PointLight");
	Shader::AddPixelShader("Asset/shader/SpecularReflection_PS.cso", "Specular");
	Shader::AddPixelShader("Asset/shader/unlitTexturePS.cso", "Unlit");
	Shader::AddPixelShader("Asset/shader/UI_BaseShader_PS.cso", "UI_Base");


	//== ImGUI設定 ==//
	ig_DebugWindow = new ImGUI_DebugWindow();
	ig_DebugWindow->SetWindowName("DebugWindow");
	ImGUIManager::AddWindow(ig_DebugWindow);

	
	//== オブジェクト設定 ==//
	
	//== ポイントライト ==//
	PointLight_Obj = new GameObject();
	
	PointLight* pointLightBuf = PointLight_Obj->AddComponent<PointLight>();
	
	pointLightBuf->SetAttenuation(1.0f, 0.0f, 0.0f);
	pointLightBuf->SetLightColor(1.0f, 0.976431f, 0.8f, 10.0f);
	
	Hierarchy.push_back(PointLight_Obj);
	
	PointLight_Obj->transform->position = Vector3(4.0f, 4.0f, 1.0f);
	
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
	
	SkyBox->AddComponent<MeshRenderer>()->Load("Asset\\model\\SkyBox_Town.obj");
	
	SkyBox->transform->scale = Vector3(30.0f, 30.0f, 30.0f);
	
	Hierarchy.push_back(SkyBox);
	

	//== 車体 ==//
	Body = new GameObject();

	Body->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Body.obj");

	Hierarchy.push_back(Body);

	MeshRenderer* meshRenderer_buf = Body->GetComponent<MeshRenderer>();

	meshRenderer_buf->GetSubset_MaterialName("BlackLuster")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Brake")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("BrakeDisc")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Carburetor")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("EmblemSilver")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Gasket")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Pedal")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Radiator")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("RadiatorParts")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("RearSuspension")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("RearTireFrame")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Showa")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Sprocket")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Suspension")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Tank")->Material.PixelShader = Shader::GetPixelShader("Specular");
	meshRenderer_buf->GetSubset_MaterialName("Winker")->Material.PixelShader = Shader::GetPixelShader("Specular");


	Body->transform->scale = Vector3(0.03f, 0.03f, 0.03f);

	
	//== マフラー ==//
	Muffler = new GameObject();
	
	Muffler->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Muffler.obj");

	Muffler->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Muffler")->Material.PixelShader = Shader::GetPixelShader("Specular");
	
	Muffler->Set_Parent(Body);
	
	//== エンジン ==//
	Engine = new GameObject();
	
	Engine->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Engine.obj");

	Engine->GetComponent<MeshRenderer>()->GetSubset_MaterialName("CrankCase")->Material.PixelShader = Shader::GetPixelShader("Specular");
	
	Engine->Set_Parent(Body);
	
	//== ハンドル ==//
	Handle = new GameObject();
	
	Handle->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_Handle.obj");

	Handle->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Handle")->Material.PixelShader = Shader::GetPixelShader("Specular");
	Handle->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Suspension")->Material.PixelShader = Shader::GetPixelShader("Specular");
	Handle->GetComponent<MeshRenderer>()->GetSubset_MaterialName("MeterFrame")->Material.PixelShader = Shader::GetPixelShader("Specular");
	Handle->GetComponent<MeshRenderer>()->GetSubset_MaterialName("MaterSilver")->Material.PixelShader = Shader::GetPixelShader("Specular");
	Handle->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Winker")->Material.PixelShader = Shader::GetPixelShader("Specular");
	Handle->GetComponent<MeshRenderer>()->GetSubset_MaterialName("HeadLightFrame")->Material.PixelShader = Shader::GetPixelShader("Specular");

	Handle->Set_Parent(Body);

	//== フロントフェンダー ==//
	FrontFender = new GameObject();
	
	FrontFender->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_FrontFender.obj");

	FrontFender->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Tank")->Material.PixelShader = Shader::GetPixelShader("Specular");
	FrontFender->GetComponent<MeshRenderer>()->GetSubset_MaterialName("Brake")->Material.PixelShader = Shader::GetPixelShader("Specular");
	FrontFender->GetComponent<MeshRenderer>()->GetSubset_MaterialName("BrakeDisc")->Material.PixelShader = Shader::GetPixelShader("Specular");
	FrontFender->GetComponent<MeshRenderer>()->GetSubset_MaterialName("SuspensionCover")->Material.PixelShader = Shader::GetPixelShader("Specular");

	FrontFender->Set_Parent(Body);
	
	//== フロントタイヤ ==//
	FrontTire = new GameObject();
	
	FrontTire->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_FrontTire.obj");

	FrontTire->Set_Parent(Body);

	//== リアタイヤ ==//
	RearTire = new GameObject();

	RearTire->AddComponent<MeshRenderer>()->Load("Asset\\model\\CB400SF\\CB400SF_RearTire.obj");

	RearTire->Set_Parent(Body);
	
	//== 地面 ==//
	Ground = new GameObject();
	
	Ground->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Ground.obj");
	
	Hierarchy.push_back(Ground);

	//== テストスフィア ==//
	Sphere = new GameObject();

	Sphere->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Sphere.obj");

	Sphere->GetComponent<MeshRenderer>()->GetSubset_Index(0)->Material.PixelShader = Shader::GetPixelShader("Specular");

	Sphere->transform->position.x = 4.0f;
	Sphere->transform->position.y = 1.0f;

	Hierarchy.push_back(Sphere);

	//== テストUI ==//
	TestUI = new GameObject();

	UISpriteRenderer* uis_buf = TestUI->AddComponent<UISpriteRenderer>();
	 
	Texture* TestUITexture;
	TestUITexture = new Texture();
	TestUITexture->Create("Asset/texture/Scope.png");
	ID3D11ShaderResourceView* TestUI_buf = TestUITexture->GetResource();

	uis_buf->SetTexture(TestUI_buf);
	uis_buf->SetVertexShader(Shader::GetVertexShader("Unlit"), Shader::GetInputLayout("Unlit"));
	uis_buf->SetPixelShader(Shader::GetPixelShader("Unlit"));

	Hierarchy.push_back(TestUI);


	//オブジェクトの描画処理
	for (const auto& e : Hierarchy)
	{
		e->Start();
	}
}

void Scene_Game::Update()
{
	//終了処理
	if (Input::GetKeyState(KEY_INPUT_ESCAPE) == Input::KEY_DOWN)
	{
		SCENE_MANAGER->LoadScene(EXIT_NUM_SCENE);
		return;
	}

	//FPS表示
	ig_DebugWindow->FPS = Time::Get_FPS();
	//時間表示
	ig_DebugWindow->GameTime = Time::GetWorldTime();

	//カメラかバイクの操作
	if (Input::GetGamePadButtonState(GAMEPAD_INPUT_X) == Input::KEY_WHILE_DOWN)
	{
		Body->transform->Translate(
			Input::GetGamePad_LeftStick().x * 0.0000001f * Time::GetDeltaTime(),
			0.0f,
			Input::GetGamePad_LeftStick().y * 0.0000001f * Time::GetDeltaTime()
		);

		Body->transform->Rotate(0.0f, Input::GetGamePad_RightStick().x * 0.0000001f * Time::GetDeltaTime(), 0.0f);

	}
	else
	{
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
	}

	TestUI->transform->position.x += 0.0001f;

	//別視点カメラ切り替え
	if (Input::GetGamePadButtonState(GAMEPAD_INPUT_BACK) == Input::KEY_WHILE_DOWN)
	{
		LightCamera->GetComponent<Camera>()->Enable = true;
		MainCamera->GetComponent<Camera>()->Enable = false;
	}
	else
	{
		LightCamera->GetComponent<Camera>()->Enable = false;
		MainCamera->GetComponent<Camera>()->Enable = true;
	}

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