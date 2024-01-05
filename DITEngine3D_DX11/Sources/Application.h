#pragma once

#include <Windows.h>
#include <cstdint>

class Application
{

private:

	HINSTANCE	hInstance;		//インスタンスハンドル
	HWND		hWnd;			//ウィンドウのハンドル
	uint32_t	WindowWidth;	//ウィンドウの横幅
	uint32_t	WindowHeight;	//ウィンドウの高さ

	bool InitApp();
	void CloseApp();
	bool InitWnd();
	void CloseWnd();
	void MainLoop();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

public:

	Application(uint32_t width, uint32_t height);
	~Application();

	void Run();

	//=============================================
	//ウィンドウの幅を取得
	uint32_t Get_WindowWidth()
	{
		return WindowWidth;
	}

	//=============================================
	//ウィンドウの高さを取得
	uint32_t Get_WindowHeight()
	{
		return WindowHeight;
	}

	//=============================================
	//ウィンドウハンドルを取得
	HWND GetWindowHandle()
	{
		return hWnd;
	}

};