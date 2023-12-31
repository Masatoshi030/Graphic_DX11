#pragma once
#include "KeyInputDifinitionList.h"
#include <SimpleMath.h>


namespace Input
{

	//�L�[�̉������
	enum KEYSTATE
	{
		KEY_DOWN,			//�L�[���������u�ԁi�P�t���[���j
		KEY_WHILE_DOWN,		//�L�[�������Ă����
		KEY_UP,				//�L�[���グ���u�ԁi�P�t���[���j
		KEY_WHILE_UP,		//�L�[���グ�Ă����
		KEY_STATE_Num		//�L�[�̉�����Ԃ̑���
	};

	//============================================
	//������
	void Init(HWND _hWnd);

	//==========================================================================
	//�L�[�̉������u�Ԃ�OS����擾���ăL�[�ꎞ�o�b�t�@�ɋL�^����֐�
	//unsigned int _KeyCode�FOS����̓��̓L�[�R�[�h�uLOWORD(wParam)�v
	//[��] SetKeyDownState(wParam)
	void SetKeyDownState(unsigned int _KeyCode);

	//==========================================================================
	//�L�[�̗������u�Ԃ�OS����擾���ăL�[�ꎞ�o�b�t�@�ɋL�^����֐�
	//unsigned int _KeyCode�FOS����̓��̓L�[�R�[�h�uLOWORD(wParam)�v
	//[��] SetKeyUpState(LOWORD(wParam))
	void SetKeyUpState(unsigned int _KeyCode);

	//==========================================================================
	//�L�[�ꎞ�o�b�t�@�𔻒f���ăL�[��Ԍ��ʂ��X�V����֐�
	//unsigned int _KeyCode�FOS����̓��̓L�[�R�[�h�uLOWORD(wParam)�v
	//[��] Update();
	void Update();

	//==============================================
	//�L�[�̉�����Ԃ��擾����֐�
	//_key�F�L�[�R�[�h
	//[��] GetKeyState(KEY_INPUT_A)
	KEYSTATE GetKeyState(int _KEY);

	//==============================================
	//�}�E�X�̃|�C���^�[���W��OS����擾���čX�V����֐�
	//[��] SetMousePointer(LOWORD(lParam))
	DirectX::SimpleMath::Vector2 SetMousePointer_OnScreen(unsigned int _MousePoint);

	//==============================================
	//�E�B���h�E��̃}�E�X�̃|�C���^�[���W���擾����֐�
	DirectX::SimpleMath::Vector2 GetMousePointer_OnScreen();

	//==============================================
	//�}�E�X�|�C���^�[�̍��W��O�t���[���̍��W�Ɣ�r���Ĉړ��ʂ��v�Z
	DirectX::SimpleMath::Vector2 GetMouseMoveValue_OnScreen();

	//==============================================
	//�}�E�X�̍��𑜓x���W���X�V���鏈��
	void SetMousePointer_HighResolution(LPARAM _lp);

	//==============================================
	//�}�E�X�̍��𑜓x���W���X�V���鏈��
	DirectX::SimpleMath::Vector2 GetMouseMoveValue_HighResolution();

	//==============================================
	//�Q�[���p�b�h�̃{�^���̉�����Ԃ��擾����֐�
	KEYSTATE GetGamePadButtonState(int _GAMEPAD_INPUT);

	//==============================================
	//�Q�[���p�b�h�̍��X�e�B�b�N�̓��͒l
	DirectX::SimpleMath::Vector2 GetGamePad_LeftStick();

	//==============================================
	//�Q�[���p�b�h�̉E�X�e�B�b�N�̓��͒l
	DirectX::SimpleMath::Vector2 GetGamePad_RightStick();

	//==============================================
	//�Q�[���p�b�h�̍��g���K�[�̓��͒l
	float GetGamePad_LeftTrigger();

	//==============================================
	//�Q�[���p�b�h�̉E�g���K�[�̓��͒l
	float GetGamePad_RightTrigger();

	//==============================================
	//�Q�[���p�b�h�̃o�C�u���[�V�������Z�b�g
	void SetGamePadVibration(float _Speed, float _Timer);
}