#include "InputSystem.h"

namespace Input
{

	//===== �ϐ��錾 =====//

	//�e�L�[�̉�����Ԃ��i�[����z��
	KEYSTATE eK_KeyStateList[KEY_TYPENUM];

	//�e�L�[�̉�����Ԃ��i�[����z��
	KEYSTATE eK_KeyStateList_buf[KEY_TYPENUM];

	//�}�E�X�̍��W
	DirectX::SimpleMath::Vector2 MousePoint;


	void Init()
	{
		//�L�[���̏������i�L�[���オ���Ă����ԁj
		for (int i = 0; i < KEY_TYPENUM; i++)
		{
			eK_KeyStateList[i] = KEY_WHILE_UP;
			eK_KeyStateList_buf[i] = KEY_WHILE_UP;
		}
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
		//�L�[���̍X�V
		for (int i = 0; i < KEY_TYPENUM; i++)
		{
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
		}
	}

	KEYSTATE GetKeyState(int _KEY)
	{
		return eK_KeyStateList[_KEY];
	}

	DirectX::SimpleMath::Vector2 GetMousePointer_OnScreen()
	{
		return MousePoint;
	}

	DirectX::SimpleMath::Vector2 SetMousePointer(unsigned int _MousePoint)
	{
		int x = _MousePoint & 0x0000ffff; //LOWORD(lParam); // �}�E�X��X���W������ϐ�
		int y = (_MousePoint & 0xffff0000) >> 16; //HIWORD(lParam); // �}�E�X��Y���W������ϐ�

		MousePoint = DirectX::SimpleMath::Vector2(x, y);

		return DirectX::SimpleMath::Vector2(x, y);
	}

}