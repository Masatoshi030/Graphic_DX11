#pragma once
#include "Component.h"
#include "SystemFormat.h"


class Transform : public Component
{
public:
	//‚RŸŒ³À•W
	Vector3 position;
	
	//‚RŸŒ³Šp“x
	Vector3 rotation;

	//‚RŸŒ³ƒXƒP[ƒ‹
	Vector3 scale;

	void Init();

	void Translate(Vector3 value);
	void Translate(float _x, float _y, float _z);

	void Rotate(Vector3 value);
	void Rotate(float _x, float _y, float _z);
};