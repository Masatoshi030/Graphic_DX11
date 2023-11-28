#pragma once
#include "KeyInputDifinitionList.h"
#include <SimpleMath.h>


namespace Input
{

	//キーの押下状態
	enum KEYSTATE
	{
		KEY_DOWN,			//キーを押した瞬間（１フレーム）
		KEY_WHILE_DOWN,		//キーを押している間
		KEY_UP,				//キーを上げた瞬間（１フレーム）
		KEY_WHILE_UP,		//キーを上げている間
		KEY_STATE_Num		//キーの押下状態の総数
	};

	//============================================
	//初期化
	void Init();

	//==========================================================================
	//キーの押した瞬間をOSから取得してキー一時バッファに記録する関数
	//unsigned int _KeyCode：OSからの入力キーコード「LOWORD(wParam)」
	//[例] SetKeyDownState(wParam)
	void SetKeyDownState(unsigned int _KeyCode);

	//==========================================================================
	//キーの離した瞬間をOSから取得してキー一時バッファに記録する関数
	//unsigned int _KeyCode：OSからの入力キーコード「LOWORD(wParam)」
	//[例] SetKeyUpState(LOWORD(wParam))
	void SetKeyUpState(unsigned int _KeyCode);

	//==========================================================================
	//キー一時バッファを判断してキー状態結果を更新する関数
	//unsigned int _KeyCode：OSからの入力キーコード「LOWORD(wParam)」
	//[例] Update();
	void Update();

	//==============================================
	//キーの押下状態を取得する関数
	//_key：キーコード
	//[例] GetKeyState(KEY_INPUT_A)
	KEYSTATE GetKeyState(int _KEY);

	//==============================================
	//マウスのポインター座標をOSから取得して更新する関数
	//[例] SetMousePointer(LOWORD(lParam))
	DirectX::SimpleMath::Vector2 SetMousePointer(unsigned int _MousePoint);

	//==============================================
	//ウィンドウ上のマウスのポインター座標を取得する関数
	DirectX::SimpleMath::Vector2 GetMousePointer_OnScreen();
}