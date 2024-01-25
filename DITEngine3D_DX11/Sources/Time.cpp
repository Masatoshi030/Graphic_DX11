#include "Time.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib") // timeGetTime�֐��̂���

namespace Time
{

	//���s���Ă���݌v�t���[����
	unsigned int FrameCounter = 0;

	//�Q�[�������s�����Ƃ��̎���
	unsigned long GameStartTime = 0;

	// �f���^�^�C���p�̕ϐ�
	DWORD DeltaTime;

	//�O�t���[���̎���
	DWORD LastTime = 0;

	//���̃t���[���̎���
	DWORD NowTime = 0;

	//���̃Q�[�����n�܂��Ă���̎��Ԃ����ԃt�H�[�}�b�g�Ŋi�[��������
	TIME WorldTime;

	//1�b�v���p�^�C�}�[
	int FPSTimer = 1000;

	//1�b�O�̃t���[����
	int LastFrameCount = 0;

	//���݂̃t���[�����[�g
	int FPS = 0;

	//���̃Q�[�����n�܂��Ă��炸���Ɨݐς����鎞�ԁ@�~���b
	unsigned long NowMMtime = 0;

	void Init()
	{
		timeBeginPeriod(1); // ���x���P�~���b�ɏグ��
		LastTime = timeGetTime();
		timeEndPeriod(1); // ���x�����ɖ߂�
	}

	void UpdateTime()
	{
		//�t���[���J�E���^�[����
		FrameCounter++;

		// �f���^�^�C���̌v��
		timeBeginPeriod(1); // ���x���P�~���b�ɏグ��
		NowTime = timeGetTime();
		timeEndPeriod(1); // ���x�����ɖ߂�
		DeltaTime = NowTime - LastTime;
		LastTime = NowTime;

		NowMMtime += DeltaTime;

		FPSTimer -= DeltaTime;

		if (FPSTimer < 1)
		{
			FPSTimer = 1000;

			//1�b�O�̃t���[�������牽�t���[���o��������FPS�����r����B
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