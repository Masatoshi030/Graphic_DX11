#pragma once

//=============================================================//
//	�V�[���}�l�[�W���[���V���O���g���ŊǗ�����N���X
//=============================================================//

#include <Windows.h>

#include "Scene_Game.h"

enum SCENE_TYPE
{
	GAME_SCENE,			//�Q�[���V�[��
	EXIT_NUM_SCENE,		//�Q�[���I���V�[�����V�[���̑���
};

#define SCENE_MANAGER SCENE_MANAGERSYSTEM::Get_Instance()

class SCENE_MANAGERSYSTEM
{
private:

	//�v���C�x�[�g�R���X�g���N�^
	SCENE_MANAGERSYSTEM() {};

	//�C���X�^���X
	static SCENE_MANAGERSYSTEM* Instance;

	//�V�[����ύX�������̃t���O
	bool bSceneChange = false;

	//���̃V�[���^�C�v
	SCENE_TYPE SceneMode = GAME_SCENE;

	//���̃V�[���̃|�C���^
	Scene* p_Scene;

public:

	//======================================================
	//�ySCENE_MANAGER�N���X�̃Q�b�^�[�z
	//�E�C���X�^���X����������Ă��Ȃ���΍쐬
	static SCENE_MANAGERSYSTEM* Get_Instance()
	{
		//�����ς݂̃C���X�^���X���Ȃ���ΐV�K�쐬
		if (Instance == NULL)
		{
			Instance = new SCENE_MANAGERSYSTEM();
		}

		//�C���X�^���X�̃|�C���^�[��Ԃ�
		return Instance;
	}

	//======================================================
	//�Q�[�����C������
	//msg�F���b�Z�[�W�n���h���̃|�C���^�[
	void Game_Main(MSG* msg);

	//======================================================
	//�V�[�������[�h����
	//_Scene�F�J�ڐ�̃V�[���^�C�v
	void LoadScene(SCENE_TYPE _Scene);

	//======================================================
	//���̃V�[�����擾
	SCENE_TYPE Get_ActiveScene();
};