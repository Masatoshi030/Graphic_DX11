#include "Texture.h"
#include <stdio.h>
#include <shlwapi.h>
#include <WICTextureLoader.h>
#include <string>
#include <wrl/client.h>
#include "utftosjisconv.h"
#include "WinMain.h"

using namespace Microsoft::WRL;

#pragma comment(lib, "shlwapi.lib")

Texture::Texture()
	:width(0), height(0),
	pSRV(nullptr),
	pTex(nullptr)
{

}

Texture::~Texture()
{
	SAFE_RELEASE(pSRV);
	SAFE_RELEASE(pTex);
}

HRESULT Texture::Create(const char* _filePath)
{
	HRESULT hr = S_OK;

	// s-jisをワイド文字に
	std::wstring ws = sjis_to_wide_winapi(_filePath);

	ComPtr<ID3D11Resource> res;

	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(
		D3D->Get_ID3D11Device(),
		ws.c_str(),
		res.GetAddressOf(),
		&pSRV);
	
	//リソース情報から画像の高さと幅を取得

	ID3D11Texture2D* pTex = 0;

	pSRV->GetResource(&res);
	res->QueryInterface<ID3D11Texture2D>(&pTex);
	D3D11_TEXTURE2D_DESC desc;
	pTex->GetDesc(&desc);

	width = (UINT)desc.Width;
	height = (UINT)desc.Height;

	return hr;
}

HRESULT Texture::Create(DXGI_FORMAT format, UINT width, UINT height, const void* pData)
{
	D3D11_TEXTURE2D_DESC desc = MakeTextureDesc(format, width, height);
	return CreateResource(desc, pData);
}

UINT Texture::GetWidth() const
{
	return width;
}
UINT Texture::GetHeight() const
{
	return height;
}
ID3D11ShaderResourceView* Texture::GetResource() const
{
	return pSRV;
}

D3D11_TEXTURE2D_DESC Texture::MakeTextureDesc(DXGI_FORMAT _format, UINT _width, UINT _height)
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = _format;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	return desc;
}

HRESULT Texture::CreateResource(D3D11_TEXTURE2D_DESC& _desc, const void* _pData)
{
	HRESULT hr = E_FAIL;

	// テクスチャ作成
	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = _pData;
	data.SysMemPitch = _desc.Width * 4;
	hr = D3D->Get_ID3D11Device()->CreateTexture2D(&_desc, _pData ? &data : nullptr, &pTex);
	if (FAILED(hr)) { return hr; }

	// 設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	switch (_desc.Format)
	{
	default:						srvDesc.Format = _desc.Format;			break;
	case DXGI_FORMAT_R32_TYPELESS: 	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;	break;
	}
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// 生成
	hr = D3D->Get_ID3D11Device()->CreateShaderResourceView(pTex, &srvDesc, &pSRV);
	if (SUCCEEDED(hr))
	{
		width = _desc.Width;
		height = _desc.Height;
	}
	return hr;
}


RenderTarget::RenderTarget() : pRTV(nullptr)
{

}

RenderTarget::~RenderTarget()
{
	SAFE_RELEASE(pRTV);
}

void RenderTarget::Clear()
{
	static float color[4] = { 0.0f,0.0f,0.0f,0.0f };
	Clear(color);
}

void RenderTarget::Clear(const float* color)
{
	D3D->Get_ID3D11DeviceContext()->ClearRenderTargetView(pRTV, color);
}

HRESULT RenderTarget::Create(DXGI_FORMAT format, UINT width, UINT height)
{
	D3D11_TEXTURE2D_DESC desc = MakeTextureDesc(format, width, height);
	desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
	return CreateResource(desc);
}

HRESULT RenderTarget::CreateFromScreen()
{
	HRESULT hr;

	//バックバッファのポインタを取得
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = D3D->Get_IDXGISwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pTex);
	if (FAILED(hr))
	{
		return hr;
	}

	//バックバッファへのポインタを指定してレンダーターゲットビューを作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.Texture2D.MipSlice = 0;
	hr = D3D->Get_ID3D11Device()->CreateRenderTargetView(pTex, &rtvDesc, &pRTV);
	if (SUCCEEDED(hr))
	{
		D3D11_TEXTURE2D_DESC desc;
		pTex->GetDesc(&desc);
		width = desc.Width;
		height = desc.Height;
	}

	return hr;
}

ID3D11RenderTargetView* RenderTarget::GetRenderTargetView() const
{
	return pRTV;
}

HRESULT RenderTarget::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// テクスチャリソース作成
	HRESULT hr = Texture::CreateResource(desc, nullptr);
	if (FAILED(hr)) { return hr; }

	// 設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = desc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// 生成
	return D3D->Get_ID3D11Device()->CreateRenderTargetView(pTex, &rtvDesc, &pRTV);
}