#include "DITEngineSystem.h"
#include "DITEngine3D.h"

namespace DITEngine
{
	MipMap EnvironmentMipMap;

	void DITEngine_Init()
	{
		//���Ԍv��������
		Time::Init();

		//���̓V�X�e��������
		Input::Init(D3D->Get_ApplicationHandle()->GetWindowHandle());
	}

	MipMap* GetEnvironmentMipMap()
	{
		return &EnvironmentMipMap;
	}
}