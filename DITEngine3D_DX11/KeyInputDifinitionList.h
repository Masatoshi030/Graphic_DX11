#pragma once

//キーの種類の総数
//キーを増やしたらここを増やす！！
#define KEY_TYPENUM				 259

//=============================//
//		キーマクロ定義一覧
//=============================//

#define KEY_INPUT_LBUTTON        0x01
#define KEY_INPUT_RBUTTON        0x02
#define KEY_INPUT_CANCEL         0x03
#define KEY_INPUT_MBUTTON        0x04
#define KEY_INPUT_XBUTTON1       0x05
#define KEY_INPUT_XBUTTON2       0x06

#define KEY_INPUT_BACK           0x08
#define KEY_INPUT_TAB            0x09

#define KEY_INPUT_CLEAR          0x0C
#define KEY_INPUT_RETURN         0x0D

#define KEY_INPUT_SHIFT          0x10
#define KEY_INPUT_CONTROL        0x11
#define KEY_INPUT_MENU           0x12
#define KEY_INPUT_PAUSE          0x13
#define KEY_INPUT_CAPITAL        0x14

#define KEY_INPUT_KANA           0x15
#define KEY_INPUT_HANGEUL        0x15
#define KEY_INPUT_HANGUL         0x15
#define KEY_INPUT_IME_ON         0x16
#define KEY_INPUT_JUNJA          0x17
#define KEY_INPUT_FINAL          0x18
#define KEY_INPUT_HANJA          0x19
#define KEY_INPUT_KANJI          0x19
#define KEY_INPUT_IME_OFF        0x1A

#define KEY_INPUT_ESCAPE         0x1B

#define KEY_INPUT_CONVERT        0x1C
#define KEY_INPUT_NONCONVERT     0x1D
#define KEY_INPUT_ACCEPT         0x1E
#define KEY_INPUT_MODECHANGE     0x1F

#define KEY_INPUT_SPACE          0x20
#define KEY_INPUT_PRIOR          0x21
#define KEY_INPUT_NEXT           0x22
#define KEY_INPUT_END            0x23
#define KEY_INPUT_HOME           0x24
#define KEY_INPUT_LEFT           0x25
#define KEY_INPUT_UP             0x26
#define KEY_INPUT_RIGHT          0x27
#define KEY_INPUT_DOWN           0x28
#define KEY_INPUT_SELECT         0x29
#define KEY_INPUT_PRINT          0x2A
#define KEY_INPUT_EXECUTE        0x2B
#define KEY_INPUT_SNAPSHOT       0x2C
#define KEY_INPUT_INSERT         0x2D
#define KEY_INPUT_DELETE         0x2E
#define KEY_INPUT_HELP           0x2F

#define KEY_INPUT_0		0x30
#define KEY_INPUT_1		0x31
#define KEY_INPUT_2		0x32
#define KEY_INPUT_3		0x33
#define KEY_INPUT_4		0x34
#define KEY_INPUT_5		0x35
#define KEY_INPUT_6		0x36
#define KEY_INPUT_7		0x37
#define KEY_INPUT_8		0x38
#define KEY_INPUT_9		0x39

#define KEY_INPUT_A		  0x41 //'A'
#define KEY_INPUT_B		  0x42
#define KEY_INPUT_C		  0x43
#define KEY_INPUT_D		  0x44
#define KEY_INPUT_E		  0x45
#define KEY_INPUT_F		  0x46
#define KEY_INPUT_G		  0x47
#define KEY_INPUT_H		  0x48
#define KEY_INPUT_I		  0x49
#define KEY_INPUT_J		  0x4A
#define KEY_INPUT_K		  0x4B
#define KEY_INPUT_L		  0x4C
#define KEY_INPUT_M		  0x4D
#define KEY_INPUT_N		  0x4E
#define KEY_INPUT_O		  0x4F
#define KEY_INPUT_P		  0x50
#define KEY_INPUT_Q		  0x51
#define KEY_INPUT_R		  0x52
#define KEY_INPUT_S		  0x53
#define KEY_INPUT_T		  0x54
#define KEY_INPUT_U		  0x55
#define KEY_INPUT_V		  0x56
#define KEY_INPUT_W		  0x57
#define KEY_INPUT_X		  0x58
#define KEY_INPUT_Y		  0x59
#define KEY_INPUT_Z		  0x5A

#define KEY_INPUT_LWIN           0x5B
#define KEY_INPUT_RWIN           0x5C
#define KEY_INPUT_APPS           0x5D
#define KEY_INPUT_SLEEP          0x5F

#define KEY_INPUT_NUMPAD0        0x60
#define KEY_INPUT_NUMPAD1        0x61
#define KEY_INPUT_NUMPAD2        0x62
#define KEY_INPUT_NUMPAD3        0x63
#define KEY_INPUT_NUMPAD4        0x64
#define KEY_INPUT_NUMPAD5        0x65
#define KEY_INPUT_NUMPAD6        0x66
#define KEY_INPUT_NUMPAD7        0x67
#define KEY_INPUT_NUMPAD8        0x68
#define KEY_INPUT_NUMPAD9        0x69

#define KEY_INPUT_MULTIPLY       0x6A
#define KEY_INPUT_ADD            0x6B
#define KEY_INPUT_SEPARATOR      0x6C
#define KEY_INPUT_SUBTRACT       0x6D
#define KEY_INPUT_DECIMAL        0x6E
#define KEY_INPUT_DIVIDE         0x6F

#define KEY_INPUT_F1             0x70
#define KEY_INPUT_F2             0x71
#define KEY_INPUT_F3             0x72
#define KEY_INPUT_F4             0x73
#define KEY_INPUT_F5             0x74
#define KEY_INPUT_F6             0x75
#define KEY_INPUT_F7             0x76
#define KEY_INPUT_F8             0x77
#define KEY_INPUT_F9             0x78
#define KEY_INPUT_F10            0x79
#define KEY_INPUT_F11            0x7A
#define KEY_INPUT_F12            0x7B
#define KEY_INPUT_F13            0x7C
#define KEY_INPUT_F14            0x7D
#define KEY_INPUT_F15            0x7E
#define KEY_INPUT_F16            0x7F
#define KEY_INPUT_F17            0x80
#define KEY_INPUT_F18            0x81
#define KEY_INPUT_F19            0x82
#define KEY_INPUT_F20            0x83
#define KEY_INPUT_F21            0x84
#define KEY_INPUT_F22            0x85
#define KEY_INPUT_F23            0x86
#define KEY_INPUT_F24            0x87

#define KEY_INPUT_NAVIGATION_VIEW     0x88
#define KEY_INPUT_NAVIGATION_MENU     0x89
#define KEY_INPUT_NAVIGATION_UP       0x8A
#define KEY_INPUT_NAVIGATION_DOWN     0x8B
#define KEY_INPUT_NAVIGATION_LEFT     0x8C
#define KEY_INPUT_NAVIGATION_RIGHT    0x8D
#define KEY_INPUT_NAVIGATION_ACCEPT   0x8E
#define KEY_INPUT_NAVIGATION_CANCEL   0x8F

#define KEY_INPUT_NUMLOCK        0x90
#define KEY_INPUT_SCROLL         0x91

#define KEY_INPUT_OEM_NEC_EQUAL  0x92
#define KEY_INPUT_OEM_FJ_JISHO   0x92
#define KEY_INPUT_OEM_FJ_MASSHOU 0x93
#define KEY_INPUT_OEM_FJ_TOUROKU 0x94
#define KEY_INPUT_OEM_FJ_LOYA    0x95
#define KEY_INPUT_OEM_FJ_ROYA    0x96

#define KEY_INPUT_LSHIFT         0xA0
#define KEY_INPUT_RSHIFT         0xA1
#define KEY_INPUT_LCONTROL       0xA2
#define KEY_INPUT_RCONTROL       0xA3
#define KEY_INPUT_LMENU          0xA4
#define KEY_INPUT_RMENU          0xA5

#define KEY_INPUT_BROWSER_BACK        0xA6
#define KEY_INPUT_BROWSER_FORWARD     0xA7
#define KEY_INPUT_BROWSER_REFRESH     0xA8
#define KEY_INPUT_BROWSER_STOP        0xA9
#define KEY_INPUT_BROWSER_SEARCH      0xAA
#define KEY_INPUT_BROWSER_FAVORITES   0xAB
#define KEY_INPUT_BROWSER_HOME        0xAC

#define KEY_INPUT_VOLUME_MUTE         0xAD
#define KEY_INPUT_VOLUME_DOWN         0xAE
#define KEY_INPUT_VOLUME_UP           0xAF

#define KEY_INPUT_MEDIA_NEXT_TRACK    0xB0
#define KEY_INPUT_MEDIA_PREV_TRACK    0xB1
#define KEY_INPUT_MEDIA_STOP          0xB2
#define KEY_INPUT_MEDIA_PLAY_PAUSE    0xB3

#define KEY_INPUT_LAUNCH_MAIL         0xB4
#define KEY_INPUT_LAUNCH_MEDIA_SELECT 0xB5
#define KEY_INPUT_LAUNCH_APP1         0xB6
#define KEY_INPUT_LAUNCH_APP2         0xB7

#define KEY_INPUT_OEM_1          0xBA
#define KEY_INPUT_OEM_PLUS       0xBB
#define KEY_INPUT_OEM_COMMA      0xBC
#define KEY_INPUT_OEM_MINUS      0xBD
#define KEY_INPUT_OEM_PERIOD     0xBE
#define KEY_INPUT_OEM_2          0xBF
#define KEY_INPUT_OEM_3          0xC0

#define KEY_INPUT_GAMEPAD_A                         0xC3
#define KEY_INPUT_GAMEPAD_B                         0xC4
#define KEY_INPUT_GAMEPAD_X                         0xC5
#define KEY_INPUT_GAMEPAD_Y                         0xC6
#define KEY_INPUT_GAMEPAD_RIGHT_SHOULDER            0xC7
#define KEY_INPUT_GAMEPAD_LEFT_SHOULDER             0xC8
#define KEY_INPUT_GAMEPAD_LEFT_TRIGGER              0xC9
#define KEY_INPUT_GAMEPAD_RIGHT_TRIGGER             0xCA
#define KEY_INPUT_GAMEPAD_DPAD_UP                   0xCB
#define KEY_INPUT_GAMEPAD_DPAD_DOWN                 0xCC
#define KEY_INPUT_GAMEPAD_DPAD_LEFT                 0xCD
#define KEY_INPUT_GAMEPAD_DPAD_RIGHT                0xCE
#define KEY_INPUT_GAMEPAD_MENU                      0xCF
#define KEY_INPUT_GAMEPAD_VIEW                      0xD0
#define KEY_INPUT_GAMEPAD_LEFT_THUMBSTICK_BUTTON    0xD1
#define KEY_INPUT_GAMEPAD_RIGHT_THUMBSTICK_BUTTON   0xD2
#define KEY_INPUT_GAMEPAD_LEFT_THUMBSTICK_UP        0xD3
#define KEY_INPUT_GAMEPAD_LEFT_THUMBSTICK_DOWN      0xD4
#define KEY_INPUT_GAMEPAD_LEFT_THUMBSTICK_RIGHT     0xD5
#define KEY_INPUT_GAMEPAD_LEFT_THUMBSTICK_LEFT      0xD6
#define KEY_INPUT_GAMEPAD_RIGHT_THUMBSTICK_UP       0xD7
#define KEY_INPUT_GAMEPAD_RIGHT_THUMBSTICK_DOWN     0xD8
#define KEY_INPUT_GAMEPAD_RIGHT_THUMBSTICK_RIGHT    0xD9
#define KEY_INPUT_GAMEPAD_RIGHT_THUMBSTICK_LEFT     0xDA

#define KEY_INPUT_OEM_4          0xDB
#define KEY_INPUT_OEM_5          0xDC
#define KEY_INPUT_OEM_6          0xDD
#define KEY_INPUT_OEM_7          0xDE
#define KEY_INPUT_OEM_8          0xDF
#define KEY_INPUT_OEM_AX         0xE1
#define KEY_INPUT_OEM_102        0xE2

#define KEY_INPUT_ICO_HELP       0xE3
#define KEY_INPUT_ICO_00         0xE4
#define KEY_INPUT_PROCESSKEY     0xE5
#define KEY_INPUT_ICO_CLEAR      0xE6
#define KEY_INPUT_PACKET         0xE7

#define KEY_INPUT_OEM_RESET      0xE9
#define KEY_INPUT_OEM_JUMP       0xEA
#define KEY_INPUT_OEM_PA1        0xEB
#define KEY_INPUT_OEM_PA2        0xEC
#define KEY_INPUT_OEM_PA3        0xED
#define KEY_INPUT_OEM_WSCTRL     0xEE
#define KEY_INPUT_OEM_CUSEL      0xEF
#define KEY_INPUT_OEM_ATTN       0xF0
#define KEY_INPUT_OEM_FINISH     0xF1
#define KEY_INPUT_OEM_COPY       0xF2
#define KEY_INPUT_OEM_AUTO       0xF3
#define KEY_INPUT_OEM_ENLW       0xF4
#define KEY_INPUT_OEM_BACKTAB    0xF5

#define KEY_INPUT_ATTN           0xF6
#define KEY_INPUT_CRSEL          0xF7
#define KEY_INPUT_EXSEL          0xF8
#define KEY_INPUT_EREOF          0xF9
#define KEY_INPUT_PLAY           0xFA
#define KEY_INPUT_ZOOM           0xFB
#define KEY_INPUT_NONAME         0xFC
#define KEY_INPUT_PA1            0xFD
#define KEY_INPUT_OEM_CLEAR      0xFE


//マウス操作関連

#define KEY_INPUT_MOUSEBUTTON_LEFT		0x100
#define KEY_INPUT_MOUSEBUTTON_RIGHT		0x101
#define KEY_INPUT_MOUSEBUTTON_WHEEL		0x102