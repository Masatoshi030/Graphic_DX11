#pragma once

class Component
{
public:

	//Componentのみでのnewを防ぐ
	Component() {}

	//コンポーネントの有効無効
	bool Enable = true;

	class GameObject* gameObject = nullptr;

	//デストラクタ
	~Component() {};

	//初期化処理
	virtual void Init() {};

	//解放処理
	virtual void Release() {};

	//初期フレーム処理
	virtual void Start() {};

	//更新処理
	virtual void Update() {};

	//描画処理
	virtual void Draw() {};
};