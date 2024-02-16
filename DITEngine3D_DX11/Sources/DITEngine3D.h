#pragma once

#include <Windows.h>
#include "SceneManager.h"
#include "Direct3D11.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "ShaderManager.h"
#include "Time.h"
#include "Texture.h"
#include "ShaderManager.h"
#include "MipMap.h"
#include "IniFileManager.h"

//ImGUI
#include "ImGUIManager.h"
#include "ImGUIWindowBase.h"

//コンポーネント
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "UISpriteRenderer.h"
#include "Spring.h"

//便利な定義

//RGBAを255の形式で引数を渡せるようにする定義
// aのみ1.00fまでの数字
//(R G B A) = (255, 255, 255, 1.0f)
#define COLOR_NORMALIZATION_255(_r, _g, _b, _a)	((float)_r / 255.0f),((float)_g / 255.0f),((float)_b / 255.0f),((float)_a)