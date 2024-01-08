#pragma once
#include "MipMap.h"

namespace DITEngine
{
	//===============================================
	//DITエンジンの初期化
	void DITEngine_Init();

	//================================================
	//環境テクスチャのミップマップを取得
	MipMap* GetEnvironmentMipMap();
}