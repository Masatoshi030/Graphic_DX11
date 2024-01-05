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
		//オブジェクトリストの解放
		for (const auto& e : Hierarchy)
		{
			//要素の解放
			delete e;
		}
	};

	virtual void Start() {};
	virtual void Update() {};
	virtual void Draw() {};

protected:

	std::list<GameObject*> Hierarchy;

};