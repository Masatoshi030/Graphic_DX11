#pragma once

#include <list>
#include "GameObject.h"
#include "ImGUIManager.h"

class Scene
{
public:

	Scene() {};

	~Scene() 
	{
		//�I�u�W�F�N�g���X�g�̉��
		for (const auto& e : Hierarchy)
		{
			//�v�f�̉��
			delete e;
		}
	};

	virtual void Start() {};
	virtual void Update() {};
	virtual void Draw() {};

protected:

	std::list<GameObject*> Hierarchy;

};