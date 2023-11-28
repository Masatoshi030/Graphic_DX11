#include "DITEngine3D.h"

GameObject::GameObject()
{
	//Transformは必須なので生成時に付ける
	transform = AddComponent<Transform>();
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