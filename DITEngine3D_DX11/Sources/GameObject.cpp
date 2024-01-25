#include "DITEngine3D.h"

GameObject::GameObject()
{
	//Transformは必須なので生成時に付ける
	transform = AddComponent<Transform>();

	//親を初期化
	parent = nullptr;
}

void GameObject::Start()
{
	for (Component* pCom : Component_List)
	{
		if (pCom->Enable)
		{
			pCom->Start();
		}
	}

	//子オブジェクトの更新処理
	for (const auto& e : ChildGameObject_List)
	{
		e->Start();
	}
}

void GameObject::Update()
{
	for (Component* pCom : Component_List)
	{
		if (pCom->Enable)
		{
			pCom->Update();
		}
	}

	//子オブジェクトの更新処理
	for (const auto& e : ChildGameObject_List)
	{
		e->Update();
	}
}

void GameObject::Draw()
{
	for (Component* pCom : Component_List)
	{
		if (pCom->Enable)
		{
			pCom->Draw();
		}
	}

	//子オブジェクトの更新処理
	for (const auto& e : ChildGameObject_List)
	{
		e->Draw();
	}
}

void GameObject::Set_Tag(const char* _tag)
{

}

void GameObject::Set_Parent(GameObject* _parent)
{
	//親のオブジェクトに子登録
	_parent->ChildGameObject_List.push_back(this);

	//自分の親を設定
	parent = _parent;
}

Component* GameObject::GetComponent(const type_info& t)
{
	for (Component* pCom : Component_List)
	{
		if (typeid(*pCom) == t)
		{
			//型が同じなら
			return pCom;
		}
	}

	return nullptr;
}