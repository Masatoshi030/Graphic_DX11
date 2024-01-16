#include "DITEngine3D.h"
#include "Scene_Game.h"
#include "DITEngineSystem.h"

void Scene_Game::Start()
{
	//== ���摜�̐ݒ�i�~�b�v���x�����ƂɃ��[�h�j ==//

	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_2000x1000.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_1000x500.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_500x250.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_250x125.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_125x62.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_62x30.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_32x14.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_14x6.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_6x2.jpg");
	DITEngine::GetEnvironmentMipMap()->AddTexture("Asset/texture/MapTexture/parking_garage_3x1.jpg");

	
	//== �V�F�[�_�[�ݒ� ==//

	//���_�V�F�[�_�[
	Shader::AddVertexShader("Asset/shader/DirectionalLight_VS.cso", "Directional");
	Shader::AddVertexShader("Asset/shader/PointLight_VS.cso", "PointLight");
	Shader::AddVertexShader("Asset/shader/unlitTextureVS.cso", "Unlit");
	Shader::AddVertexShader("Asset/shader/UI_BaseShader_VS.cso", "UI_Base");

	//�s�N�Z���V�F�[�_�[
	Shader::AddPixelShader("Asset/shader/SpecularReflection_PS.cso", "Specular");
	Shader::AddPixelShader("Asset/shader/DirectionalLight_PS.cso", "Directional");
	Shader::AddPixelShader("Asset/shader/PointLight_PS.cso", "PointLight");
	Shader::AddPixelShader("Asset/shader/unlitTexturePS.cso", "Unlit");
	Shader::AddPixelShader("Asset/shader/UI_BaseShader_PS.cso", "UI_Base");


	//== ImGUI�ݒ� ==//

	//�f�o�b�O�E�B���h�E
	ig_DebugWindow = new ImGUI_DebugWindow();
	ig_DebugWindow->SetWindowName("DebugWindow");
	ImGUIManager::AddWindow(ig_DebugWindow);

	//�}�e���A���E�B���h�E
	ig_MaterialWindow = new ImGUI_MaterialWindow();
	ig_MaterialWindow->SetWindowName("MaterialWindow");
	ImGUIManager::AddWindow(ig_MaterialWindow);

	
	//== �I�u�W�F�N�g�ݒ� ==//
	
	//== �T�����C�g ==//
	DirectionalLight_Obj = new GameObject();

	DirectionalLight* DirLight_buf = DirectionalLight_Obj->AddComponent<DirectionalLight>();

	Hierarchy.push_back(DirectionalLight_Obj);
	
	//== ���C���J���� ==//
	MainCamera = new GameObject();
	
	MainCamera->AddComponent<Camera>();

	Hierarchy.push_back(MainCamera);
	
	
	//== �X�J�C�{�b�N�X ==//
	SkyBox = new GameObject();
	
	SkyBox->AddComponent<MeshRenderer>()->Load("Asset\\model\\SkyBox_Town.obj");
	
	SkyBox->transform->scale = Vector3(30.0f, 30.0f, 30.0f);

	SkyBox->GetComponent<MeshRenderer>()->GetSubset_Index(0)->Material.VertexShader = Shader::GetVertexShader("Unlit");
	SkyBox->GetComponent<MeshRenderer>()->GetSubset_Index(0)->Material.PixelShader = Shader::GetPixelShader("Unlit");
	
	Hierarchy.push_back(SkyBox);
	

	//== �e�X�g�X�t�B�A ==//
	Sphere = new GameObject();

	Sphere->AddComponent<MeshRenderer>()->Load("Asset\\model\\BaseModel\\Sphere.obj");

	Sphere->transform->position.y = 1.0f;

	Hierarchy.push_back(Sphere);

	ig_MaterialWindow->AddMaterialEditor_MeshRenderer(Sphere->GetComponent<MeshRenderer>());

	//== �e�X�gUI ==//
	TestUI = new GameObject();

	UISpriteRenderer* uis_buf = TestUI->AddComponent<UISpriteRenderer>();
	 
	Texture* TestUITexture;
	TestUITexture = new Texture();
	TestUITexture->Create("Asset/texture/DITEngine_Logo.png");
	ID3D11ShaderResourceView* TestUI_buf = TestUITexture->GetResource();

	uis_buf->SetTexture(TestUI_buf);
	uis_buf->SetVertexShader(Shader::GetVertexShader("UI_Base"), Shader::GetInputLayout("UI_Base"));
	uis_buf->SetPixelShader(Shader::GetPixelShader("UI_Base"));

	//�f�o�b�O�E�B���h�E�̏�����
	ig_DebugWindow->UI_Position_X_Slider = TestUI->transform->position.x;
	ig_DebugWindow->UI_Position_Y_Slider = TestUI->transform->position.y;

	ig_DebugWindow->UI_Rotation_Slider = TestUI->transform->rotation.z;

	ig_DebugWindow->UI_Scale_X_Slider = TestUI->transform->scale.x;
	ig_DebugWindow->UI_Scale_Y_Slider = TestUI->transform->scale.y;

	Hierarchy.push_back(TestUI);

	
	//�}�e���A���f�[�^�ǂݍ��ݏ���
	ig_MaterialWindow->Init();

	//�f�o�b�O�f�[�^�ǂݍ��ݏ���
	ig_DebugWindow->Init();


	//�I�u�W�F�N�g�̕`�揈��
	for (const auto& e : Hierarchy)
	{
		e->Start();
	}
}

void Scene_Game::Update()
{
	//== �I������ ==//
	if (Input::GetKeyState(KEY_INPUT_ESCAPE) == Input::KEY_DOWN)
	{
		SCENE_MANAGER->LoadScene(EXIT_NUM_SCENE);
		return;
	}

	//== �f�o�b�O�E�B���h�E�̒l��ݒ� ==//

	//FPS�\��
	ig_DebugWindow->FPS = Time::Get_FPS();
	//���ԕ\��
	ig_DebugWindow->GameTime = Time::GetWorldTime();

	//���W
	TestUI->transform->position.x = ig_DebugWindow->UI_Position_X_Slider;
	TestUI->transform->position.y = ig_DebugWindow->UI_Position_Y_Slider;
	//��]
	TestUI->transform->rotation.z = DirectX::XMConvertToRadians(ig_DebugWindow->UI_Rotation_Slider);
	//�X�P�[��
	TestUI->transform->scale.x = ig_DebugWindow->UI_Scale_X_Slider;
	TestUI->transform->scale.y = ig_DebugWindow->UI_Scale_Y_Slider;


	//DirectionalLight
	DirectionalLight* DirLight_buf = DirectionalLight_Obj->GetComponent<DirectionalLight>();

	DirLight_buf->SetLightColor(ig_DebugWindow->Light_Diffuse);
	DirLight_buf->SetAmbient(ig_DebugWindow->Light_Ambient);
	DirLight_buf->SetDirection(ig_DebugWindow->Light_Direction);


	//== �o�C�u���[�V�����e�X�g ==//

	//�o�C�u���[�V�����e�X�g
	if (Input::GetGamePadButtonState(GAMEPAD_INPUT_B) == Input::KEY_DOWN)
	{
		Input::SetGamePadVibration(1.0f, 0.25f);
	}


	//�I�u�W�F�N�g�̕`�揈��
	for (const auto& e : Hierarchy)
	{
		e->Update();
	}
}

void Scene_Game::Draw()
{

	//== ��ʂ�h��Ԃ� ==//
	float color[4] = { COLOR_NORMALIZATION_255(44, 70, 112, 1.0f) };
	D3D->Get_ID3D11DeviceContext()->ClearRenderTargetView(D3D->Get_RenderTargetView(), color);


	//== ���_�̏����V�F�[�_�[�ɑ��� ==//
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