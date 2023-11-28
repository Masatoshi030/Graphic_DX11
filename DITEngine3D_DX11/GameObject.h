#pragma once

#include <list>
#include <typeinfo>

#include "Component.h"
#include "Transform.h"
#include "Camera.h"

class GameObject
{
protected:

	std::list<Component*> Component_List;
	std::list<GameObject*> ChildGameObject_List;

public:

	Transform* transform;

	//名前
	char name[20] = "NoName";

	//タグ
	char tag[20] = "NoTag";

	//静的オブジェクト
	bool bStatic = false;

	GameObject();
	~GameObject() 
	{
		//子オブジェクトの解放
		for (const auto& e : ChildGameObject_List)
		{
			delete e;
		}

		//コンポーネントの解放
		for (const auto& e : Component_List)
		{
			delete e;
		}
	};

	//初期処理
	void Start();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	//オブジェクトが持っているコンポーネントを取得
	template <typename T>
	T* GetComponent()
	{
		return (T*)GetComponent(typeid(T));
	};

	//コンポーネントをゲームオブジェクトに追加する
	template <typename T>
	T* AddComponent()
	{
		//Tの型でコンポーネントを作成
		T* component = new T();

		//コンポーネントリストに追加
		Component_List.push_back(component);

		//持ち主を設定
		((Component*)component)->gameObject = this;

		//初期化
		((Component*)component)->Init();

		return component;
	}

	//タグの設定
	void Set_Tag(const char* _tag);

private:

	Component* GetComponent(const type_info& t);

};