#include "Time.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib") // timeGetTime関数のため

namespace Time
{

	//実行してから累計フレーム数
	unsigned int FrameCounter = 0;

	//ゲームを実行したときの時間
	unsigned long GameStartTime = 0;

	// デルタタイム用の変数
	DWORD DeltaTime;

	//前フレームの時間
	DWORD LastTime = 0;

	//今のフレームの時間
	DWORD NowTime = 0;

	//このゲームが始まってからの時間を時間フォーマットで格納したもの
	TIME WorldTime;

	//1秒計測用タイマー
	int FPSTimer = 1000;

	//1秒前のフレーム数
	int LastFrameCount = 0;

	//現在のフレームレート
	int FPS = 0;

	//このゲームが始まってからずっと累積させる時間　ミリ秒
	unsigned long NowMMtime = 0;

	void Init()
	{
		timeBeginPeriod(1); // 精度を１ミリ秒に上げる
		LastTime = timeGetTime();
		timeEndPeriod(1); // 精度を元に戻す
	}

	void UpdateTime()
	{
		//フレームカウンター増加
		FrameCounter++;

		// デルタタイムの計測
		timeBeginPeriod(1); // 精度を１ミリ秒に上げる
		NowTime = timeGetTime();
		timeEndPeriod(1); // 精度を元に戻す
		DeltaTime = NowTime - LastTime;
		LastTime = NowTime;

		NowMMtime += DeltaTime;

		FPSTimer -= DeltaTime;

		if (FPSTimer < 1)
		{
			FPSTimer = 1000;

			//1秒前のフレーム数から何フレーム経ったかでFPSを研鑽する。
			FPS = FrameCounter - LastFrameCount;
			LastFrameCount = FrameCounter;
		}

	}

	unsigned int Get_FrameCounter()
	{
		return FrameCounter;
	}

	unsigned long  GetDeltaTime()
	{
		return DeltaTime;
	}

	TIME GetWorldTime()
	{
		WorldTime.Set_TimeWithSerial(NowMMtime);
		return WorldTime;
	}

	int Get_FPS()
	{
		return FPS;
	}
}