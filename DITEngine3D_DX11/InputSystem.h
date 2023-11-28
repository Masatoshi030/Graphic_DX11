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
	void Init();

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
	DirectX::SimpleMath::Vector2 SetMousePointer(unsigned int _MousePoint);

	//==============================================
	//�E�B���h�E��̃}�E�X�̃|�C���^�[���W���擾����֐�
	DirectX::SimpleMath::Vector2 GetMousePointer_OnScreen();
}