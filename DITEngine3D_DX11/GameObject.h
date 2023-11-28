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

	//���O
	char name[20] = "NoName";

	//�^�O
	char tag[20] = "NoTag";

	//�ÓI�I�u�W�F�N�g
	bool bStatic = false;

	GameObject();
	~GameObject() 
	{
		//�q�I�u�W�F�N�g�̉��
		for (const auto& e : ChildGameObject_List)
		{
			delete e;
		}

		//�R���|�[�l���g�̉��
		for (const auto& e : Component_List)
		{
			delete e;
		}
	};

	//��������
	void Start();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�I�u�W�F�N�g�������Ă���R���|�[�l���g���擾
	template <typename T>
	T* GetComponent()
	{
		return (T*)GetComponent(typeid(T));
	};

	//�R���|�[�l���g���Q�[���I�u�W�F�N�g�ɒǉ�����
	template <typename T>
	T* AddComponent()
	{
		//T�̌^�ŃR���|�[�l���g���쐬
		T* component = new T();

		//�R���|�[�l���g���X�g�ɒǉ�
		Component_List.push_back(component);

		//�������ݒ�
		((Component*)component)->gameObject = this;

		//������
		((Component*)component)->Init();

		return component;
	}

	//�^�O�̐ݒ�
	void Set_Tag(const char* _tag);

private:

	Component* GetComponent(const type_info& t);

};