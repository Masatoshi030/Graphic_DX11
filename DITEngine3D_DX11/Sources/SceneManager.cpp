#include "DITEngine3D.h"

#include "Scene_Game.h"

//�V���O���g���@�C���X�^���X
SCENE_MANAGERSYSTEM* SCENE_MANAGERSYSTEM::Instance = nullptr;

void SCENE_MANAGERSYSTEM::Game_Main(MSG* msg)
{

	do
	{
		//�V�[���J�ڃt���O�@���Z�b�g
		bSceneChange = false;

		//�V�[�����쐬
		switch (SceneMode)
		{

		case GAME_SCENE:
			p_Scene = new Scene_Game();
			break;

		default:
			//�����U�蕪���ł��Ȃ���΂��̂܂܏I��
			p_Scene = nullptr;
			break;
		}

		//�V�[���Ƀf�[�^�������Ă�Ώ����J�n
		if (p_Scene != nullptr)
		{

			//�V�[���̏�������
			p_Scene->Start();

			//���C�����[�v
			while (bSceneChange == false)
			{

				//�O��̃��[�v���烆�[�U���삪�����������ׂ�
				BOOL MessageExit = PeekMessage(msg, NULL, 0, 0, PM_REMOVE);

				//���̓V�X�e���X�V����
				Input::Update();

				if (MessageExit)
				{
					//�ԐړI�ɃE�B���h�E�v���V�[�W�����Ă�
					DispatchMessage(msg);

					//�A�v���I������
					if (msg->message == WM_QUIT)
					{
						//�I��
						LoadScene(EXIT_NUM_SCENE);
					}
				}
				else
				{
					//== �Q�[�����[�v ==//

					//���ԍX�V����
					Time::UpdateTime();

					//�V�[���̍X�V����
					p_Scene->Update();

					//�I���ł͂Ȃ����
					if (SceneMode != EXIT_NUM_SCENE)
					{
						//�`��J�n
						D3D->Render_DrawBegin();

						//�V�[���̕`�揈��
						p_Scene->Draw();

						//ImGUI�̕`��
						ImGUIManager::Draw();

						//�`��I�� �_�u���o�b�t�@�؂�ւ�
						D3D->Render_DrawEnd();
					}
				}

				LPARAM lp = 0;

				Input::SetMousePointer_HighResolution(lp);
			}
		}

		//�V�[���̉��
		delete p_Scene;


		//�J�ڐ�̃V�[����EXIT�������烋�[�v�I��
	} while (SceneMode != EXIT_NUM_SCENE);
}

void SCENE_MANAGERSYSTEM::LoadScene(SCENE_TYPE _Scene)
{
	bSceneChange = true;
	SceneMode = _Scene;
}

SCENE_TYPE SCENE_MANAGERSYSTEM::Get_ActiveScene()
{
	return SceneMode;
}