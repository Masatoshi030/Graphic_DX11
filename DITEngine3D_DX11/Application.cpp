#include "Application.h"
#include "DITEngine3D.h"

const auto ClassName = TEXT("DIT�G���W��3D");
const auto WindowName = TEXT("DIT�G���W��3D");

//�R���X�g���N�^
Application::Application(uint32_t _Width, uint32_t _Height)
	: hInstance(nullptr)
	,hWnd(nullptr)
	,WindowWidth(_Width)
	,WindowHeight(_Height)
{

}

//�f�X�g���N�^
Application::~Application() {};

//���s
void Application::Run()
{
	//�A�v���P�[�V�����J�n�ɐ���������
	if (InitApp())
	{
		//���C�����[�v�������s
		MainLoop();
	}

	//�A�v���P�[�V�����I��
	CloseApp();
}




void Application::MainLoop()
{
	//���b�Z�[�W�n���h��
	MSG msg;

	//�V�[���}�l�[�W���[�̃Q�[������
	SCENE_MANAGER->Game_Main(&msg);

}

bool Application::InitApp()
{
	//�E�B���h�E������
	if (!InitWnd())
	{
		//�ُ�I��
		return false;
	}

	//DIRECT3D11��������
	D3D->Init(this);

	//���Ԍv��������
	Time::Init();

	//DITEngine�V�X�e���֘A�̏�����
	Input::Init();

	//����I��
	return true;
}

//�I������
void Application::CloseApp()
{
	//�E�B���h�E�̏I������
	CloseWnd();
}

bool Application::InitWnd()
{
	//�C���X�^���X�n���h�����擾
	auto hInstance_buf = GetModuleHandle(nullptr);

	if (hInstance_buf == nullptr)
	{
		return false;
	}

	//�E�B���h�E�̐ݒ�
	WNDCLASSEX WC = {};
	WC.cbSize = sizeof(WNDCLASSEX);
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc = WndProc;
	WC.hIcon = LoadIcon(hInstance_buf, IDI_APPLICATION);
	WC.hCursor = LoadCursor(hInstance_buf, IDC_ARROW);
	WC.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
	WC.lpszMenuName = nullptr;
	WC.lpszClassName = ClassName;
	WC.hIconSm = LoadIcon(hInstance_buf, IDI_APPLICATION);

	//�E�B���h�E�̓o�^
	if (!RegisterClassEx(&WC))
	{
		return false;
	}

	//�C���X�^���X�n���h���ݒ�
	hInstance = hInstance_buf;

	//�E�B���h�E�T�C�Y��ݒ�
	RECT RC = {};
	RC.right = static_cast<LONG>(WindowWidth);
	RC.bottom = static_cast<LONG>(WindowHeight);

	//�E�B���h�E�T�C�Y�𒲐�
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&RC, style, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx
	(
		0,
		ClassName,
		WindowName,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		RC.right - RC.left,
		RC.bottom - RC.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (hWnd == nullptr)
	{
		return false;
	}

	//�E�B���h�E��\��
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//�E�B���h�E���X�V
	UpdateWindow(hWnd);

	//�E�B���h�E�Ƀt�H�[�J�X
	SetFocus(hWnd);

	//����I��
	return true;
}

//�E�B���h�E�̏I������
void Application::CloseWnd()
{
	//�E�B���h�E�̓o�^������
	if (hInstance != nullptr)
	{
		UnregisterClass(ClassName, hInstance);
	}

	hInstance = nullptr;
	hWnd = nullptr;
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:// �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);// �gWM_QUIT�h���b�Z�[�W�𑗂�@���@�A�v���I��
		break;

	case WM_CLOSE:  // x�{�^���������ꂽ��
		DestroyWindow(hWnd);  // �gWM_DESTROY�h���b�Z�[�W�𑗂�
		break;


	case WM_LBUTTONDOWN: // ���N���b�N���ꂽ�Ƃ�

		Input::SetKeyDownState(KEY_INPUT_MOUSEBUTTON_LEFT);

		break;

	case WM_LBUTTONUP: // ���N���b�N���オ�����Ƃ�

		Input::SetKeyUpState(KEY_INPUT_MOUSEBUTTON_LEFT);

		break;


	case WM_RBUTTONDOWN: // �E�N���b�N���ꂽ�Ƃ�

		Input::SetKeyDownState(KEY_INPUT_MOUSEBUTTON_RIGHT);

		break;

	case WM_RBUTTONUP: // �E�N���b�N���ꂽ�Ƃ�

		Input::SetKeyUpState(KEY_INPUT_MOUSEBUTTON_RIGHT);

		break;

	case WM_MBUTTONDOWN: // �z�C�[���N���b�N���ꂽ�Ƃ�

		Input::SetKeyDownState(KEY_INPUT_MOUSEBUTTON_WHEEL);

		break;

	case WM_MBUTTONUP: // �z�C�[���N���b�N���ꂽ�Ƃ�

		Input::SetKeyUpState(KEY_INPUT_MOUSEBUTTON_WHEEL);

		break;

	case WM_MOUSEMOVE: // �}�E�X�J�[�\�����������Ƃ�
	{
		Input::SetMousePointer(lp);
	}
	break;

	case WM_KEYDOWN:

		//�Q�[���p�L�[���͎擾����
		Input::SetKeyDownState(LOWORD(wp));

		break;

	case WM_KEYUP:

		Input::SetKeyUpState(LOWORD(wp));

		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}