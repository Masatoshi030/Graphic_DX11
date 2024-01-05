#include "WinMain.h"
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//アプリケーション実行
	Application app(SCREEN_WIDTH, SCREEN_HEIGHT);

	app.Run();

	return 0;
}