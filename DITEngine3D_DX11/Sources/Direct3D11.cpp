#include "Direct3D11.h"

#include <io.h>
#include <DirectXMath.h>


using namespace DirectX::SimpleMath;
using namespace DirectX;


//シングルトン　インスタンス
DIRECT3D11* DIRECT3D11::Instance = nullptr;

void DIRECT3D11::Init(Application* _APP)
{
	HRESULT hr = S_OK;

	//持ち主オブジェクトのアドレスをセット
	App = _APP;


	//デバイス・スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = App->Get_WindowWidth();
	swapChainDesc.BufferDesc.Height = App->Get_WindowHeight();
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = App->GetWindowHandle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&SwapChain,
		&Device,
		&FeatureLevel,
		&DeviceContext
	);


	//レンダーターゲットビュー作成
	//描画先の画像
	ID3D11Texture2D* renderTarget{};
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	Device->CreateRenderTargetView(renderTarget, NULL, &RenderTargetView);
	renderTarget->Release();


	//デプスステンシルバッファ作成
	//陰で見えない部分を省略するシステムの計算領域
	ID3D11Texture2D* depthStencile{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);


	//デプスステンシルビュー作成
	//陰で見えない部分を省略するシステムの計算領域
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &DepthStencilView);
	depthStencile->Release();

	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);


	//ビューポート設定
	//表示領域
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)App->Get_WindowWidth();
	viewport.Height = (FLOAT)App->Get_WindowHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	DeviceContext->RSSetViewports(1, &viewport);


	//ラスタライザステート設定
	//リアルタイム 3D グラフィックスを表示するために、(図形やプリミティブで構成された) ベクター情報を (ピクセルで構成された) ラスター画像に変換
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	//	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	//	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	Device->CreateRasterizerState(&rasterizerDesc, &rs);

	DeviceContext->RSSetState(rs);


	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	Device->CreateBlendState(&blendDesc, &BlendState);

	blendDesc.AlphaToCoverageEnable = TRUE;
	Device->CreateBlendState(&blendDesc, &BlendStateATC);

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	DeviceContext->OMSetBlendState(BlendState, blendFactor, 0xffffffff);


	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	Device->CreateDepthStencilState(&depthStencilDesc, &DepthStateEnable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	Device->CreateDepthStencilState(&depthStencilDesc, &DepthStateDisable);//深度無効ステート

	DeviceContext->OMSetDepthStencilState(DepthStateEnable, NULL);


	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState{};
	Device->CreateSamplerState(&samplerDesc, &samplerState);

	DeviceContext->PSSetSamplers(0, 1, &samplerState);


	//定数バッファ
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(XMMATRIX);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	Device->CreateBuffer(&bufferDesc, NULL, &WorldBuffer);
	DeviceContext->VSSetConstantBuffers(0, 1, &WorldBuffer);

	Device->CreateBuffer(&bufferDesc, NULL, &ViewBuffer);
	DeviceContext->VSSetConstantBuffers(1, 1, &ViewBuffer);

	Device->CreateBuffer(&bufferDesc, NULL, &ProjectionBuffer);
	DeviceContext->VSSetConstantBuffers(2, 1, &ProjectionBuffer);


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	Device->CreateBuffer(&bufferDesc, NULL, &MaterialBuffer);
	DeviceContext->VSSetConstantBuffers(3, 1, &MaterialBuffer);
	DeviceContext->PSSetConstantBuffers(3, 1, &MaterialBuffer);


	bufferDesc.ByteWidth = sizeof(LIGHT);

	Device->CreateBuffer(&bufferDesc, NULL, &LightBuffer);
	DeviceContext->VSSetConstantBuffers(4, 1, &LightBuffer);
	DeviceContext->PSSetConstantBuffers(4, 1, &LightBuffer);


	bufferDesc.ByteWidth = sizeof(LIGHT_POINT);

	Device->CreateBuffer(&bufferDesc, NULL, &PointLightBuffer);
	DeviceContext->VSSetConstantBuffers(5, 1, &PointLightBuffer);
	DeviceContext->PSSetConstantBuffers(5, 1, &PointLightBuffer);


	bufferDesc.ByteWidth = sizeof(EYE_INFO);

	Device->CreateBuffer(&bufferDesc, NULL, &EyeInfoBuffer);
	DeviceContext->VSSetConstantBuffers(6, 1, &EyeInfoBuffer);
	DeviceContext->PSSetConstantBuffers(6, 1, &EyeInfoBuffer);


	bufferDesc.ByteWidth = sizeof(ENVIRONMENTMAP_INFO);

	Device->CreateBuffer(&bufferDesc, NULL, &EnvironmentMapInfoBuffer);
	DeviceContext->VSSetConstantBuffers(7, 1, &EnvironmentMapInfoBuffer);
	DeviceContext->PSSetConstantBuffers(7, 1, &EnvironmentMapInfoBuffer);


	bufferDesc.ByteWidth = sizeof(XMMATRIX);

	Device->CreateBuffer(&bufferDesc, NULL, &UIInfoBuffer);
	DeviceContext->VSSetConstantBuffers(8, 1, &UIInfoBuffer);
	DeviceContext->PSSetConstantBuffers(8, 1, &UIInfoBuffer);


	bufferDesc.ByteWidth = sizeof(GPU_SYSTEM_INFO);

	Device->CreateBuffer(&bufferDesc, NULL, &SystemInfoBuffer);
	DeviceContext->VSSetConstantBuffers(9, 1, &SystemInfoBuffer);
	DeviceContext->PSSetConstantBuffers(9, 1, &SystemInfoBuffer);


	// ライト初期化
	LIGHT light{};
	light.Enable = true;
	light.Direction = Vector4(0.5f, -1.0f, 0.8f, 0.0f);
	light.Direction.Normalize();
	light.Ambient = Color(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = Color(1.5f, 1.5f, 1.5f, 1.0f);
	SetLight(light);


	// マテリアル初期化
	MATERIAL material{};
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = Color(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
}

void DIRECT3D11::Render_DrawBegin()
{
	float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	DeviceContext->ClearRenderTargetView(RenderTargetView, clearColor);
	DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DIRECT3D11::Render_DrawEnd()
{
	SwapChain->Present(1, 0);
}

void DIRECT3D11::Release()
{

	//定数バッファーを解放
	WorldBuffer->Release();
	ViewBuffer->Release();
	ProjectionBuffer->Release();
	LightBuffer->Release();
	PointLightBuffer->Release();
	MaterialBuffer->Release();

	//D3Dシステム
	DeviceContext->ClearState();
	RenderTargetView->Release();
	SwapChain->Release();
	DeviceContext->Release();
	Device->Release();
}

void DIRECT3D11::SetDepthEnable(bool Enable)
{
	if (Enable)
	{
		DeviceContext->OMSetDepthStencilState(DepthStateEnable, NULL);
	}
	else
	{
		DeviceContext->OMSetDepthStencilState(DepthStateDisable, NULL);
	}
}

void DIRECT3D11::SetATCEnable(bool Enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
	{
		DeviceContext->OMSetBlendState(BlendStateATC, blendFactor, 0xffffffff);
	}
	else
	{
		DeviceContext->OMSetBlendState(BlendState, blendFactor, 0xffffffff);
	}
}

void DIRECT3D11::SetWorldViewProjection2D()
{
	Matrix world;
	world = Matrix::Identity;			// 単位行列にする
	world = world.Transpose();			// 転置
	DeviceContext->UpdateSubresource(WorldBuffer, 0, NULL, &world, 0, 0);

	Matrix view;
	view = Matrix::Identity;
	view = view.Transpose();
	DeviceContext->UpdateSubresource(ViewBuffer, 0, NULL, &view, 0, 0);

	Matrix projection;
	/*
	// update 右手系＝＝＝＞左手系  （DIRECTXTKのメソッドは右手系だった） 20230511 update by tomoki.suzuki　
		projection = projection.CreateOrthographicOffCenter(
			static_cast<float>(m_Application->GetWidth() * -0.5f),			// ビューボリュームの最小Ｘ
			static_cast<float>(m_Application->GetWidth() * 0.5f),			// ビューボリュームの最大Ｘ
			static_cast<float>(m_Application->GetHeight() * 0.5f),			// ビューボリュームの最小Ｙ
			static_cast<float>(m_Application->GetHeight() * -0.5f),			// ビューボリュームの最大Ｙ
			0.0f,
			1000.0f);
	*/

	/*
		// update 右手系＝＝＝＞左手系  （DIRECTXTKのメソッドは右手系だった） 20230511 update by tomoki.suzuki　
		projection = DirectX::XMMatrixOrthographicOffCenterLH(
			static_cast<float>(m_Application->GetWidth() * -0.5f),			// ビューボリュームの最小Ｘ
			static_cast<float>(m_Application->GetWidth() * 0.5f),			// ビューボリュームの最大Ｘ
			static_cast<float>(m_Application->GetHeight() * 0.5f),			// ビューボリュームの最小Ｙ
			static_cast<float>(m_Application->GetHeight() * -0.5f),			// ビューボリュームの最大Ｙ
			0.0f,
			1000.0f);
	*/

	// 2D描画を左上原点にする  (20230512 update by tomoki.suzuki　
	projection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,
		static_cast<float>(App->Get_WindowWidth()),					// ビューボリュームの最小Ｘ
		static_cast<float>(App->Get_WindowHeight()),					// ビューボリュームの最小Ｙ
		0.0f,															// ビューボリュームの最大Ｙ
		0.0f,
		1.0f);


	projection = projection.Transpose();

	DeviceContext->UpdateSubresource(ProjectionBuffer, 0, NULL, &projection, 0, 0);
}

void DIRECT3D11::SetWorldMatrix(XMMATRIX* WorldMatrix)
{
	XMMATRIX world;
	world = XMMatrixTranspose(*WorldMatrix);					// 転置

	DeviceContext->UpdateSubresource(WorldBuffer, 0, NULL, &world, 0, 0);
}


void DIRECT3D11::SetViewMatrix(XMMATRIX* ViewMatrix)
{
	XMMATRIX view;
	view = XMMatrixTranspose(*ViewMatrix);						// 転置

	DeviceContext->UpdateSubresource(ViewBuffer, 0, NULL, &view, 0, 0);
}

void DIRECT3D11::SetProjectionMatrix(XMMATRIX* ProjectionMatrix)
{
	XMMATRIX projection;
	projection = XMMatrixTranspose(*ProjectionMatrix);

	DeviceContext->UpdateSubresource(ProjectionBuffer, 0, NULL, &projection, 0, 0);
}



void DIRECT3D11::SetMaterial(MATERIAL Material)
{
	DeviceContext->UpdateSubresource(MaterialBuffer, 0, NULL, &Material, 0, 0);
}

void DIRECT3D11::SetLight(LIGHT Light)
{
	DeviceContext->UpdateSubresource(LightBuffer, 0, NULL, &Light, 0, 0);
}

void DIRECT3D11::SetPointLight(LIGHT_POINT Light_Point)
{
	DeviceContext->UpdateSubresource(PointLightBuffer, 0, NULL, &Light_Point, 0, 0);
}

void DIRECT3D11::SetEyeInfo(EYE_INFO Eye_Info)
{
	DeviceContext->UpdateSubresource(EyeInfoBuffer, 0, NULL, &Eye_Info, 0, 0);
}

void DIRECT3D11::SetEnvironmentMapInfo(ENVIRONMENTMAP_INFO EnvironmentMap_Info)
{
	DeviceContext->UpdateSubresource(EnvironmentMapInfoBuffer, 0, NULL, &EnvironmentMap_Info, 0, 0);
}

void DIRECT3D11::SetUIInfoBuffer(DirectX::XMMATRIX* _UI_Info)
{
	DirectX::XMMATRIX UI_Info_buf = *_UI_Info;

	//転置
	UI_Info_buf = DirectX::XMMatrixTranspose(UI_Info_buf);

	DeviceContext->UpdateSubresource(UIInfoBuffer, 0, NULL, &UI_Info_buf, 0, 0);
}

void DIRECT3D11::SetGPUSystemInfo(GPU_SYSTEM_INFO _System_Info)
{
	DeviceContext->UpdateSubresource(SystemInfoBuffer, 0, NULL, &_System_Info, 0, 0);
}

void DIRECT3D11::CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName)
{

	FILE* file;
	long int fsize;

	fopen_s(&file, FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,		D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	4 * 3,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	4 * 6,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0,	4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	Device->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}



void DIRECT3D11::CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName)
{
	FILE* file;
	long int fsize;

	fopen_s(&file, FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}