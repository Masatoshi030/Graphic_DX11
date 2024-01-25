#include "DITEngineSystem.h"
#include "DITEngine3D.h"

namespace DITEngine
{
	MipMap EnvironmentMipMap;

	void DITEngine_Init()
	{
		//時間計測初期化
		Time::Init();

		//入力システム初期化
		Input::Init(D3D->Get_ApplicationHandle()->GetWindowHandle());
	}

	MipMap* GetEnvironmentMipMap()
	{
		return &EnvironmentMipMap;
	}
}