#pragma once

#include <Windows.h>
#include <cstdint>

class Application
{

private:

	HINSTANCE	hInstance;		//�C���X�^���X�n���h��
	HWND		hWnd;			//�E�B���h�E�̃n���h��
	uint32_t	WindowWidth;	//�E�B���h�E�̉���
	uint32_t	WindowHeight;	//�E�B���h�E�̍���

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
	//�E�B���h�E�̕����擾
	uint32_t Get_WindowWidth()
	{
		return WindowWidth;
	}

	//=============================================
	//�E�B���h�E�̍������擾
	uint32_t Get_WindowHeight()
	{
		return WindowHeight;
	}

	//=============================================
	//�E�B���h�E�n���h�����擾
	HWND GetWindowHandle()
	{
		return hWnd;
	}

};