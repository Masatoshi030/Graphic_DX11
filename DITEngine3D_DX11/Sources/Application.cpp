#include "Application.h"
#include "DITEngine3D.h"

const auto ClassName = TEXT("DITエンジン3D");
const auto WindowName = TEXT("DITエンジン3D");

//コンストラクタ
Application::Application(uint32_t _Width, uint32_t _Height)
	: hInstance(nullptr)
	,hWnd(nullptr)
	,WindowWidth(_Width)
	,WindowHeight(_Height)
{

}

//デストラクタ
Application::~Application() {};

//実行
void Application::Run()
{
	//アプリケーション開始に成功したら
	if (InitApp())
	{
		//メインループ処理実行
		MainLoop();
	}

	//アプリケーション終了
	CloseApp();
}




void Application::MainLoop()
{
	//メッセージハンドル
	MSG msg;

	//シーンマネージャーのゲーム処理
	SCENE_MANAGER->Game_Main(&msg);

}

bool Application::InitApp()
{
	//ウィンドウ初期化
	if (!InitWnd())
	{
		//異常終了
		return false;
	}

	//DIRECT3D11を初期化
	D3D->Init(this);

	//時間計測初期化
	Time::Init();

	//DITEngineシステム関連の初期化
	Input::Init(hWnd);

	//ImGUI初期化
	ImGUIManager::Init(hWnd, D3D->Get_ID3D11Device(), D3D->Get_ID3D11DeviceContext());

	//正常終了
	return true;
}

//終了処理
void Application::CloseApp()
{
	//ウィンドウの終了処理
	CloseWnd();

	//ImGUIの終了処理
	ImGUIManager::Shutdown();

	//DirectX11の終了処理
	D3D->Release();
}

bool Application::InitWnd()
{
	//インスタンスハンドルを取得
	auto hInstance_buf = GetModuleHandle(nullptr);

	if (hInstance_buf == nullptr)
	{
		return false;
	}

	//ウィンドウの設定
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

	//ウィンドウの登録
	if (!RegisterClassEx(&WC))
	{
		return false;
	}

	//インスタンスハンドル設定
	hInstance = hInstance_buf;

	//ウィンドウサイズを設定
	RECT RC = {};
	RC.right = static_cast<LONG>(WindowWidth);
	RC.bottom = static_cast<LONG>(WindowHeight);

	//ウィンドウサイズを調節
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&RC, style, FALSE);

	//ウィンドウを生成
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

	//ウィンドウを表示
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//ウィンドウを更新
	UpdateWindow(hWnd);

	//ウィンドウにフォーカス
	SetFocus(hWnd);

	//正常終了
	return true;
}

//ウィンドウの終了処理
void Application::CloseWnd()
{
	//ウィンドウの登録を解除
	if (hInstance != nullptr)
	{
		UnregisterClass(ClassName, hInstance);
	}

	hInstance = nullptr;
	hWnd = nullptr;
}

//ImGUIに入力メッセージを転送する関数のプロトタイプ宣言
LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//ウィンドウプロシージャ
LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

	//ImGuiに入力メッセージ情報を送る
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp))
	{
		return true;
	}

	switch (msg)
	{
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// “WM_QUIT”メッセージを送る　→　アプリ終了
		break;

	case WM_CLOSE:  // xボタンが押されたら
		DestroyWindow(hWnd);  // “WM_DESTROY”メッセージを送る
		break;


	case WM_LBUTTONDOWN: // 左クリックされたとき

		Input::SetKeyDownState(KEY_INPUT_MOUSEBUTTON_LEFT);

		break;

	case WM_LBUTTONUP: // 左クリックが上がったとき

		Input::SetKeyUpState(KEY_INPUT_MOUSEBUTTON_LEFT);

		break;


	case WM_RBUTTONDOWN: // 右クリックされたとき

		Input::SetKeyDownState(KEY_INPUT_MOUSEBUTTON_RIGHT);

		break;

	case WM_RBUTTONUP: // 右クリックされたとき

		Input::SetKeyUpState(KEY_INPUT_MOUSEBUTTON_RIGHT);

		break;

	case WM_MBUTTONDOWN: // ホイールクリックされたとき

		Input::SetKeyDownState(KEY_INPUT_MOUSEBUTTON_WHEEL);

		break;

	case WM_MBUTTONUP: // ホイールクリックされたとき

		Input::SetKeyUpState(KEY_INPUT_MOUSEBUTTON_WHEEL);

		break;

	case WM_MOUSEMOVE: // マウスカーソルが動いたとき（スクリーン上）
	
		Input::SetMousePointer_OnScreen(lp);
	
	break;

	case WM_INPUT:

		Input::SetMousePointer_HighResolution(lp);

		break;

	case WM_KEYDOWN:

		//ゲーム用キー入力取得処理
		Input::SetKeyDownState(LOWORD(wp));

		break;

	case WM_KEYUP:

		Input::SetKeyUpState(LOWORD(wp));

		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}