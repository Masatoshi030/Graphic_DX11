#include "InputSystem.h"

namespace Input
{

	//===== 変数宣言 =====//

	//各キーの押下状態を格納する配列
	KEYSTATE eK_KeyStateList[KEY_TYPENUM];

	//各キーの押下状態を格納する配列
	KEYSTATE eK_KeyStateList_buf[KEY_TYPENUM];

	//マウスの座標
	DirectX::SimpleMath::Vector2 MousePoint;


	void Init()
	{
		//キー情報の初期化（キーが上がっている状態）
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
		//キー情報の更新
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
		int x = _MousePoint & 0x0000ffff; //LOWORD(lParam); // マウスのX座標を入れる変数
		int y = (_MousePoint & 0xffff0000) >> 16; //HIWORD(lParam); // マウスのY座標を入れる変数

		MousePoint = DirectX::SimpleMath::Vector2(x, y);

		return DirectX::SimpleMath::Vector2(x, y);
	}

}