#include "InputSystem.h"
#include "Time.h"

#include <Xinput.h>
#pragma comment (lib, "xinput.lib")

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC		((USHORT) 0x01)
#endif // !HID_USAGE_PAGE_GENERIC

#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE		((USHORT) 0x02)
#endif // !HID_USAGE_GENERIC_MOUSE


namespace Input
{

	//===== 変数宣言 =====//

	//キーボード

	//各キーの押下状態を格納する配列
	KEYSTATE eK_KeyStateList[KEY_TYPENUM];

	//各キーの押下状態を格納する配列バッファー
	KEYSTATE eK_KeyStateList_buf[KEY_TYPENUM];

	//スクリーンDPI上のマウスの座標
	DirectX::SimpleMath::Vector2 MousePoint_OnScreen;

	//スクリーンDPI上のマウスの移動量
	DirectX::SimpleMath::Vector2 MouseMoveValue_OnScreen;
	
	//高解像度マウス移動量
	DirectX::SimpleMath::Vector2 MouseMoveValue_HighResolution;

	//高解像度マウスのデッド値
	float MouseDead = 0.001f;

	
	//XBOXコントローラー

	//ゲームパッドの各ボタンの押下状態を格納する配列
	KEYSTATE eK_GamePadButtonList[GAMEPAD_INPUT_NUM];

	//ゲームパッドの各ボタンの押下状態を格納する配列バッファー
	KEYSTATE eK_GamePadButtonList_buf[GAMEPAD_INPUT_NUM];

	//ゲームパッドの左スティックの入力状態
	DirectX::SimpleMath::Vector2 GamePad_LeftStick;

	//ゲームパッドの右スティックの入力状態
	DirectX::SimpleMath::Vector2 GamePad_RightStick;

	//ゲームパッドの左トリガーの入力状態
	float GamePad_LeftTrigger = 0.0f;

	//ゲームパッドの右トリガーの入力状態
	float GamePad_RightTrigger = 0.0f;

	//ゲームパッドの振動タイマー
	float GamePad_VibrationTimer = 0.0f;



	void Init(HWND _hWnd)
	{
		//キー情報の初期化（キーが上がっている状態）
		for (int i = 0; i < KEY_TYPENUM; i++)
		{
			//キーボード
			eK_KeyStateList[i] = KEY_WHILE_UP;
			eK_KeyStateList_buf[i] = KEY_WHILE_UP;

			//ゲームパッド
			if (i < GAMEPAD_INPUT_NUM)
			{
				eK_GamePadButtonList[i] = KEY_WHILE_UP;
				eK_GamePadButtonList_buf[i] = KEY_WHILE_UP;
			}
		}

		//マウスの登録
		RAWINPUTDEVICE Rid[1];
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = _hWnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));
	}

	void SetKeyDownState(unsigned int _KeyCode)
	{
		eK_KeyStateList_buf[_KeyCode] = KEY_DOWN;
	}

	void SetKeyUpState(unsigned int _KeyCode)
	{
		eK_KeyStateList_buf[_KeyCode] = KEY_UP;
	}

	void Update()
	{

		//== Xboxコントローラーの更新 ==//

		XINPUT_STATE state;
		XInputGetState(0, &state);

		for (int i = 0; i < GAMEPAD_INPUT_NUM; i++)
		{
			eK_GamePadButtonList_buf[i] = KEY_UP;
		}

		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)  eK_GamePadButtonList_buf[GAMEPAD_INPUT_DPAD_UP] = KEY_DOWN;//ゲームパッド十字キー上
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)  eK_GamePadButtonList_buf[GAMEPAD_INPUT_DPAD_DOWN] = KEY_DOWN;//ゲームパッド十字キー下
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) eK_GamePadButtonList_buf[GAMEPAD_INPUT_DPAD_LEFT] = KEY_DOWN;//ゲームパッド十字キー左
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) eK_GamePadButtonList_buf[GAMEPAD_INPUT_DPAD_RIGHT] = KEY_DOWN;//ゲームパッド十字キー右
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) eK_GamePadButtonList_buf[GAMEPAD_INPUT_LB] = KEY_DOWN;//ゲームパッドL
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) eK_GamePadButtonList_buf[GAMEPAD_INPUT_RB] = KEY_DOWN;//ゲームパッドR
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) eK_GamePadButtonList_buf[GAMEPAD_INPUT_LT] = KEY_DOWN;//ゲームパッドL
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) eK_GamePadButtonList_buf[GAMEPAD_INPUT_RT] = KEY_DOWN;//ゲームパッドR
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) eK_GamePadButtonList_buf[GAMEPAD_INPUT_A] = KEY_DOWN;//ゲームパッドA
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) eK_GamePadButtonList_buf[GAMEPAD_INPUT_B] = KEY_DOWN;//ゲームパッドB
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) eK_GamePadButtonList_buf[GAMEPAD_INPUT_X] = KEY_DOWN;//ゲームパッドX
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) eK_GamePadButtonList_buf[GAMEPAD_INPUT_Y] = KEY_DOWN;//ゲームパッドY
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) eK_GamePadButtonList_buf[GAMEPAD_INPUT_START] = KEY_DOWN;//ゲームパッドX
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) eK_GamePadButtonList_buf[GAMEPAD_INPUT_BACK] = KEY_DOWN;//ゲームパッドY
		
		//スティック
		GamePad_LeftStick = DirectX::SimpleMath::Vector2(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
		GamePad_RightStick = DirectX::SimpleMath::Vector2(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);

		//トリガー
		GamePad_LeftTrigger = state.Gamepad.bLeftTrigger;
		GamePad_RightTrigger = state.Gamepad.bRightTrigger;

		GamePad_LeftTrigger /= 255.0f;
		GamePad_RightTrigger /= 255.0f;

		//デッドゾーンの設定

		//左スティック
		if (state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			if (state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				GamePad_LeftStick.x = 0.0f;
				GamePad_LeftStick.y = 0.0f;
			}
		}
		//右スティック
		if (state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			if (state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				GamePad_RightStick.x = 0.0f;
				GamePad_RightStick.y = 0.0f;
			}
		}

		//バイブレーション
		if (GamePad_VibrationTimer > 0.0f)
		{
			//タイマースタート
			GamePad_VibrationTimer -= Time::GetDeltaTime() * 0.001f;

			//カウントが0秒になるとバイブレーションを停止
			if (GamePad_VibrationTimer < 0.0f)
			{
				XINPUT_VIBRATION vibration;
				vibration.wLeftMotorSpeed = 0;
				vibration.wRightMotorSpeed = 0;

				//バイブレーションを停止させる
				XInputSetState(0, &vibration);

				//タイマーをリセット
				GamePad_VibrationTimer = 0.0f;
			}
		}




		//== キーの入力状態割り振り ==//

		//キーとゲームパッドのボタン情報の更新
		for (int i = 0; i < KEY_TYPENUM; i++)
		{

			//キーボード
			if (eK_KeyStateList_buf[i] == KEY_DOWN)
			{
				switch (eK_KeyStateList[i])
				{
				case KEY_DOWN:
					eK_KeyStateList[i] = KEY_WHILE_DOWN;
					break;
				case KEY_WHILE_DOWN:
					eK_KeyStateList[i] = KEY_WHILE_DOWN;
					break;
				case KEY_UP:
					eK_KeyStateList[i] = KEY_DOWN;
					break;
				case KEY_WHILE_UP:
					eK_KeyStateList[i] = KEY_DOWN;
					break;
				}
			}
			else if (eK_KeyStateList_buf[i] == KEY_UP)
			{
				switch (eK_KeyStateList[i])
				{
				case KEY_DOWN:
					eK_KeyStateList[i] = KEY_UP;
					break;
				case KEY_WHILE_DOWN:
					eK_KeyStateList[i] = KEY_UP;
					break;
				case KEY_UP:
					eK_KeyStateList[i] = KEY_WHILE_UP;
					break;
				case KEY_WHILE_UP:
					eK_KeyStateList[i] = KEY_WHILE_UP;
					break;
				}
			}

			if (i < GAMEPAD_INPUT_NUM)
			{
				//ゲームパッド
				if (eK_GamePadButtonList_buf[i] == KEY_DOWN)
				{
					switch (eK_GamePadButtonList[i])
					{
						case KEY_DOWN:
							eK_GamePadButtonList[i] = KEY_WHILE_DOWN;
							break;
						case KEY_WHILE_DOWN:
							eK_GamePadButtonList[i] = KEY_WHILE_DOWN;
							break;
						case KEY_UP:
							eK_GamePadButtonList[i] = KEY_DOWN;
							break;
						case KEY_WHILE_UP:
							eK_GamePadButtonList[i] = KEY_DOWN;
							break;
					}
				}
				else if (eK_GamePadButtonList_buf[i] == KEY_UP)
				{
					switch (eK_GamePadButtonList[i])
					{
						case KEY_DOWN:
							eK_GamePadButtonList[i] = KEY_UP;
							break;
						case KEY_WHILE_DOWN:
							eK_GamePadButtonList[i] = KEY_UP;
							break;
						case KEY_UP:
							eK_GamePadButtonList[i] = KEY_WHILE_UP;
							break;
						case KEY_WHILE_UP:
							eK_GamePadButtonList[i] = KEY_WHILE_UP;
							break;
					}
				}
			}
		}
	}

	KEYSTATE GetKeyState(int _KEY)
	{
		return eK_KeyStateList[_KEY];
	}

	DirectX::SimpleMath::Vector2 GetMousePointer_OnScreen()
	{
		return MousePoint_OnScreen;
	}

	DirectX::SimpleMath::Vector2 GetMouseMoveValue_OnScreen() 
	{
		return MouseMoveValue_OnScreen;
	}

	DirectX::SimpleMath::Vector2 SetMousePointer_OnScreen(unsigned int _MousePoint)
	{
		int x = _MousePoint & 0x0000ffff; //LOWORD(lParam); // マウスのX座標を入れる変数
		int y = (_MousePoint & 0xffff0000) >> 16; //HIWORD(lParam); // マウスのY座標を入れる変数

		MouseMoveValue_OnScreen = DirectX::SimpleMath::Vector2(x - MousePoint_OnScreen.x, y - MousePoint_OnScreen.y);

		MousePoint_OnScreen = DirectX::SimpleMath::Vector2(x, y);

		return DirectX::SimpleMath::Vector2(x, y);
	}


	void SetMousePointer_HighResolution(LPARAM _lp)
	{
		UINT dwSize = sizeof(RAWINPUT);
		static BYTE lpb[sizeof(RAWINPUT)];

		GetRawInputData((HRAWINPUT)_lp, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

		RAWINPUT* raw = (RAWINPUT*)lpb;

		if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			MouseMoveValue_HighResolution.x = raw->data.mouse.lLastX;
			MouseMoveValue_HighResolution.y = raw->data.mouse.lLastY;

			MouseMoveValue_HighResolution *= 0.01f;
		}
	}


	DirectX::SimpleMath::Vector2 GetMouseMoveValue_HighResolution()
	{

		DirectX::SimpleMath::Vector2 returnValue;

		if (abs(MouseMoveValue_HighResolution.x) > MouseDead)
		{
			returnValue.x = MouseMoveValue_HighResolution.x;
		}

		if (abs(MouseMoveValue_HighResolution.y) > MouseDead)
		{
			returnValue.y = MouseMoveValue_HighResolution.y;
		}

		return returnValue;
	}

	KEYSTATE GetGamePadButtonState(int _GAMEPAD_INPUT)
	{
		return eK_GamePadButtonList[_GAMEPAD_INPUT];
	}

	DirectX::SimpleMath::Vector2 GetGamePad_LeftStick()
	{
		return GamePad_LeftStick;
	}

	DirectX::SimpleMath::Vector2 GetGamePad_RightStick()
	{
		return GamePad_RightStick;
	}

	float GetGamePad_LeftTrigger()
	{
		return GamePad_LeftTrigger;
	}

	float GetGamePad_RightTrigger()
	{
		return GamePad_RightTrigger;
	}

	void SetGamePadVibration(float _Speed, float _Timer)
	{
		XINPUT_VIBRATION vibration;

		//XInputの65535の値に直す
		vibration.wLeftMotorSpeed = _Speed * 65535.0f;
		vibration.wRightMotorSpeed = _Speed * 65535.0f;

		//タイマーをセット
		GamePad_VibrationTimer = _Timer;

		//バイブレーションを開始する
		XInputSetState(0, &vibration);
	}
}