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

	//===== �ϐ��錾 =====//

	//�L�[�{�[�h

	//�e�L�[�̉�����Ԃ��i�[����z��
	KEYSTATE eK_KeyStateList[KEY_TYPENUM];

	//�e�L�[�̉�����Ԃ��i�[����z��o�b�t�@�[
	KEYSTATE eK_KeyStateList_buf[KEY_TYPENUM];

	//�X�N���[��DPI��̃}�E�X�̍��W
	DirectX::SimpleMath::Vector2 MousePoint_OnScreen;

	//�X�N���[��DPI��̃}�E�X�̈ړ���
	DirectX::SimpleMath::Vector2 MouseMoveValue_OnScreen;
	
	//���𑜓x�}�E�X�ړ���
	DirectX::SimpleMath::Vector2 MouseMoveValue_HighResolution;

	//���𑜓x�}�E�X�̃f�b�h�l
	float MouseDead = 0.001f;

	
	//XBOX�R���g���[���[

	//�Q�[���p�b�h�̊e�{�^���̉�����Ԃ��i�[����z��
	KEYSTATE eK_GamePadButtonList[GAMEPAD_INPUT_NUM];

	//�Q�[���p�b�h�̊e�{�^���̉�����Ԃ��i�[����z��o�b�t�@�[
	KEYSTATE eK_GamePadButtonList_buf[GAMEPAD_INPUT_NUM];

	//�Q�[���p�b�h�̍��X�e�B�b�N�̓��͏��
	DirectX::SimpleMath::Vector2 GamePad_LeftStick;

	//�Q�[���p�b�h�̉E�X�e�B�b�N�̓��͏��
	DirectX::SimpleMath::Vector2 GamePad_RightStick;

	//�Q�[���p�b�h�̍��g���K�[�̓��͏��
	float GamePad_LeftTrigger = 0.0f;

	//�Q�[���p�b�h�̉E�g���K�[�̓��͏��
	float GamePad_RightTrigger = 0.0f;

	//�Q�[���p�b�h�̐U���^�C�}�[
	float GamePad_VibrationTimer = 0.0f;



	void Init(HWND _hWnd)
	{
		//�L�[���̏������i�L�[���オ���Ă����ԁj
		for (int i = 0; i < KEY_TYPENUM; i++)
		{
			//�L�[�{�[�h
			eK_KeyStateList[i] = KEY_WHILE_UP;
			eK_KeyStateList_buf[i] = KEY_WHILE_UP;

			//�Q�[���p�b�h
			if (i < GAMEPAD_INPUT_NUM)
			{
				eK_GamePadButtonList[i] = KEY_WHILE_UP;
				eK_GamePadButtonList_buf[i] = KEY_WHILE_UP;
			}
		}

		//�}�E�X�̓o�^
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

		//== Xbox�R���g���[���[�̍X�V ==//

		XINPUT_STATE state;
		XInputGetState(0, &state);

		for (int i = 0; i < GAMEPAD_INPUT_NUM; i++)
		{
			eK_GamePadButtonList_buf[i] = KEY_UP;
		}

		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)  eK_GamePadButtonList_buf[GAMEPAD_INPUT_DPAD_UP] = KEY_DOWN;//�Q�[���p�b�h�\���L�[��
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)  eK_GamePadButtonList_buf[GAMEPAD_INPUT_DPAD_DOWN] = KEY_DOWN;//�Q�[���p�b�h�\���L�[��
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) eK_GamePadButtonList_buf[GAMEPAD_INPUT_DPAD_LEFT] = KEY_DOWN;//�Q�[���p�b�h�\���L�[��
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) eK_GamePadButtonList_buf[GAMEPAD_INPUT_DPAD_RIGHT] = KEY_DOWN;//�Q�[���p�b�h�\���L�[�E
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) eK_GamePadButtonList_buf[GAMEPAD_INPUT_LB] = KEY_DOWN;//�Q�[���p�b�hL
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) eK_GamePadButtonList_buf[GAMEPAD_INPUT_RB] = KEY_DOWN;//�Q�[���p�b�hR
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) eK_GamePadButtonList_buf[GAMEPAD_INPUT_LT] = KEY_DOWN;//�Q�[���p�b�hL
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) eK_GamePadButtonList_buf[GAMEPAD_INPUT_RT] = KEY_DOWN;//�Q�[���p�b�hR
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) eK_GamePadButtonList_buf[GAMEPAD_INPUT_A] = KEY_DOWN;//�Q�[���p�b�hA
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) eK_GamePadButtonList_buf[GAMEPAD_INPUT_B] = KEY_DOWN;//�Q�[���p�b�hB
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) eK_GamePadButtonList_buf[GAMEPAD_INPUT_X] = KEY_DOWN;//�Q�[���p�b�hX
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) eK_GamePadButtonList_buf[GAMEPAD_INPUT_Y] = KEY_DOWN;//�Q�[���p�b�hY
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) eK_GamePadButtonList_buf[GAMEPAD_INPUT_START] = KEY_DOWN;//�Q�[���p�b�hX
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) eK_GamePadButtonList_buf[GAMEPAD_INPUT_BACK] = KEY_DOWN;//�Q�[���p�b�hY
		
		//�X�e�B�b�N
		GamePad_LeftStick = DirectX::SimpleMath::Vector2(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
		GamePad_RightStick = DirectX::SimpleMath::Vector2(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);

		//�g���K�[
		GamePad_LeftTrigger = state.Gamepad.bLeftTrigger;
		GamePad_RightTrigger = state.Gamepad.bRightTrigger;

		GamePad_LeftTrigger /= 255.0f;
		GamePad_RightTrigger /= 255.0f;

		//�f�b�h�]�[���̐ݒ�

		//���X�e�B�b�N
		if (state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			if (state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				GamePad_LeftStick.x = 0.0f;
				GamePad_LeftStick.y = 0.0f;
			}
		}
		//�E�X�e�B�b�N
		if (state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			if (state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				GamePad_RightStick.x = 0.0f;
				GamePad_RightStick.y = 0.0f;
			}
		}

		//�o�C�u���[�V����
		if (GamePad_VibrationTimer > 0.0f)
		{
			//�^�C�}�[�X�^�[�g
			GamePad_VibrationTimer -= Time::GetDeltaTime() * 0.001f;

			//�J�E���g��0�b�ɂȂ�ƃo�C�u���[�V�������~
			if (GamePad_VibrationTimer < 0.0f)
			{
				XINPUT_VIBRATION vibration;
				vibration.wLeftMotorSpeed = 0;
				vibration.wRightMotorSpeed = 0;

				//�o�C�u���[�V�������~������
				XInputSetState(0, &vibration);

				//�^�C�}�[�����Z�b�g
				GamePad_VibrationTimer = 0.0f;
			}
		}




		//== �L�[�̓��͏�Ԋ���U�� ==//

		//�L�[�ƃQ�[���p�b�h�̃{�^�����̍X�V
		for (int i = 0; i < KEY_TYPENUM; i++)
		{

			//�L�[�{�[�h
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
				//�Q�[���p�b�h
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
		int x = _MousePoint & 0x0000ffff; //LOWORD(lParam); // �}�E�X��X���W������ϐ�
		int y = (_MousePoint & 0xffff0000) >> 16; //HIWORD(lParam); // �}�E�X��Y���W������ϐ�

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

		//XInput��65535�̒l�ɒ���
		vibration.wLeftMotorSpeed = _Speed * 65535.0f;
		vibration.wRightMotorSpeed = _Speed * 65535.0f;

		//�^�C�}�[���Z�b�g
		GamePad_VibrationTimer = _Timer;

		//�o�C�u���[�V�������J�n����
		XInputSetState(0, &vibration);
	}
}