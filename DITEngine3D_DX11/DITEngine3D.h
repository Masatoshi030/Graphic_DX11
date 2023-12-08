#pragma once

#include <Windows.h>
#include "SceneManager.h"
#include "Direct3D11.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "ShaderManager.h"
#include "Texture.h"

//�R���|�[�l���g
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Light.h"

//�֗��Ȓ�`

//RGBA��255�̌`���ň�����n����悤�ɂ����`
// a�̂�1.00f�܂ł̐���
//(R G B A) = (255, 255, 255, 1.0f)
#define COLOR_NORMALIZATION_255(_r, _g, _b, _a)	((float)_r / 255.0f),((float)_g / 255.0f),((float)_b / 255.0f),((float)_a)

void DITEngine_Init();