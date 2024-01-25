#include "DITEngine3D.h"

GameObject::GameObject()
{
	//Transform�͕K�{�Ȃ̂Ő������ɕt����
	transform = AddComponent<Transform>();

	//�e��������
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

	//�q�I�u�W�F�N�g�̍X�V����
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

	//�q�I�u�W�F�N�g�̍X�V����
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

	//�q�I�u�W�F�N�g�̍X�V����
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
	//�e�̃I�u�W�F�N�g�Ɏq�o�^
	_parent->ChildGameObject_List.push_back(this);

	//�����̐e��ݒ�
	parent = _parent;
}

Component* GameObject::GetComponent(const type_info& t)
{
	for (Component* pCom : Component_List)
	{
		if (typeid(*pCom) == t)
		{
			//�^�������Ȃ�
			return pCom;
		}
	}

	return nullptr;
}