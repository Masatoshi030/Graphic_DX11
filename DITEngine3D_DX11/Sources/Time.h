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

	//���s���Ă���݌v�t���[�������擾����֐�
	//���݂̗݌v�t���[����������B
	unsigned int Get_FrameCounter();

	//Time�@�\�̏�������
	void Init();

	//���ԋ@�\�̍X�V�����i���K�{ �Q�[�����[�v�ɓ����j
	void UpdateTime();

	//�f���^�^�C�����擾
	unsigned long GetDeltaTime();

	//�Q�[�����n�܂��Ă��獡�̎��Ԃ������b�̌`���Ŏ���
	TIME GetWorldTime();

	//�t���[�����[�g���擾�ł���
	int Get_FPS();

}