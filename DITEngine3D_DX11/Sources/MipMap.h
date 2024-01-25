#pragma once
#include <vector>

#include "Texture.h"

//�~�b�v�}�b�v���Ǘ�����N���X
class MipMap
{
private:
	std::vector<Texture*> TextureList;

public:

	MipMap() {};

	//===========================================
	//�摜���Ō���ɒǉ�����
	void AddTexture(const char* _filePath);

	//===========================================
	//�w��̃~�b�v���x���̃e�N�X�`�����擾
	//�����X�g�̗v�f���𒴂����Q�Ƃ����ꂽ�ꍇ�Anullptr��Ԃ��B
	Texture* GetTexture_MipLevel(unsigned int _mipLevel);

	//===========================================
	//�e�N�X�`���̑������擾
	unsigned int GetTextureCount();

	//===========================================
	//�������
	void Release();
};