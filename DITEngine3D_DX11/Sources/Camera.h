#pragma once
#include "Component.h"
#include "SystemFormat.h"

// カメラを表すクラス
class Camera : public Component
{

private:

	DirectX::XMMATRIX viewMatrix;

	bool lookAt = false;

public:

	//初期化処理
	void Init();

	//解放処理
	void Release();

	//初期フレーム処理
	void Start();

	//更新処理
	void Update();

	//描画処理
	void Draw();


	//lookAt
	void Set_lookAt(bool _value)
	{
		lookAt = _value;
	}

	bool Get_lookAt()
	{
		return lookAt;
	}

};