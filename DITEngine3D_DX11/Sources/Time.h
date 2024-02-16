#pragma once

class TIME
{
public:

	int MMSecond = 0;
	int Second = 0;
	int Minutes = 0;
	int Hour = 0;

	TIME() {};

	TIME(int _Second, int _Minutes, int _Hour, int _MMSecond)
	{
		MMSecond = _MMSecond;
		Second = _Second;
		Minutes = _Minutes;
		Hour = _Hour;
	};

	void Set_TimeWithSerial(unsigned long SerialValue)
	{
		MMSecond = SerialValue % 1000;
		Second = (SerialValue / 1000) % 60;
		Hour = (SerialValue / 1000) / 3600;
		Minutes = (SerialValue / 1000) - (Second + (Hour * 3600));
		Minutes /= 60;
	};

	float Get_Second_Float()
	{
		return (float)Second + ((float)MMSecond / 1000.0f);
	}

};

namespace Time
{

	//実行してから累計フレーム数を取得する関数
	//現在の累計フレーム数を取れる。
	unsigned int Get_FrameCounter();

	//Time機能の初期処理
	void Init();

	//時間機能の更新処理（※必須 ゲームループに入れる）
	void UpdateTime();

	//デルタタイムを取得
	unsigned long GetDeltaTime();

	//ゲームが始まってから今の時間を時分秒の形式で取れる
	TIME GetWorldTime();

	//フレームレートを取得できる
	int Get_FPS();

}