#pragma once
#include <vector>

#include "Texture.h"

//ミップマップを管理するクラス
class MipMap
{
private:
	std::vector<Texture*> TextureList;

public:

	MipMap() {};

	//===========================================
	//画像を最後尾に追加する
	void AddTexture(const char* _filePath);

	//===========================================
	//指定のミップレベルのテクスチャを取得
	//※リストの要素数を超えた参照がされた場合、nullptrを返す。
	Texture* GetTexture_MipLevel(unsigned int _mipLevel);

	//===========================================
	//テクスチャの総数を取得
	unsigned int GetTextureCount();

	//===========================================
	//解放処理
	void Release();
};