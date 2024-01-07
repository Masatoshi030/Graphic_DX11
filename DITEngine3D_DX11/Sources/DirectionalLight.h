#pragma once
#include "Component.h"
#include "SystemFormat.h"
#include "Direct3D11.h"

// ポイントライトのコンポーネント
class DirectionalLight : public Component
{

private:

	LIGHT light;

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

	void SetLightColor(Vector4 _Color);

	void SetAmbient(Vector4 _Color);

	void SetDirection(Vector3 _Dir);
};