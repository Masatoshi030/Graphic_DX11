#pragma once

#include "Direct3D11.h"

class Texture
{
public:
	Texture();
	virtual ~Texture();
	HRESULT Create(const char* _filePath);
	HRESULT Create(DXGI_FORMAT _format, UINT _width, UINT _height, const void* _pData = nullptr);

	UINT GetWidth() const;
	UINT GetHeight() const;
	ID3D11ShaderResourceView* GetResource() const;

protected:
	D3D11_TEXTURE2D_DESC MakeTextureDesc(DXGI_FORMAT _format, UINT _width, UINT _height);
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& _desc, const void* _pData);

	UINT width;		///< ‰¡•
	UINT height;	///< c•
	ID3D11ShaderResourceView* pSRV;
	ID3D11Texture2D* pTex;
};

class RenderTarget : public Texture
{
public:
	RenderTarget();
	~RenderTarget();
	void Clear();
	void Clear(const float* color);
	HRESULT Create(DXGI_FORMAT format, UINT width, UINT height);
	HRESULT CreateFromScreen();
	ID3D11RenderTargetView* GetRenderTargetView() const;

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11RenderTargetView* pRTV;
};