#include "MipMap.h"

#include "DITEngine3D.h"

void MipMap::AddTexture(const char* _filePath)
{
	//テクスチャの読み込み
	Texture* texture_buf = new Texture();
	texture_buf->Create(_filePath);

	//リストに追加
	TextureList.push_back(texture_buf);
}

Texture* MipMap::GetTexture_MipLevel(unsigned int _mipLevel)
{
	if (_mipLevel < TextureList.size())
	{
		return 	TextureList[_mipLevel];
	}

	return nullptr;
}

unsigned int MipMap::GetTextureCount()
{
	return TextureList.size();
}

void MipMap::Release()
{
	//テクスチャを全て解放
	for (const auto& e : TextureList)
	{
		delete e;
	}
}