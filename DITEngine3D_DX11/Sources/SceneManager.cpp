#include "DITEngine3D.h"

#include "Scene_Game.h"

//シングルトン　インスタンス
SCENE_MANAGERSYSTEM* SCENE_MANAGERSYSTEM::Instance = nullptr;

void SCENE_MANAGERSYSTEM::Game_Main(MSG* msg)
{

	do
	{
		//シーン遷移フラグ　リセット
		bSceneChange = false;

		//シーンを作成
		switch (SceneMode)
		{

		case GAME_SCENE:
			p_Scene = new Scene_Game();
			break;

		default:
			//何も振り分けできなければそのまま終了
			p_Scene = nullptr;
			break;
		}

		//シーンにデータが入ってれば処理開始
		if (p_Scene != nullptr)
		{

			//シーンの初期処理
			p_Scene->Start();

			//メインループ
			while (bSceneChange == false)
			{

				//前回のループからユーザ操作があったか調べる
				BOOL MessageExit = PeekMessage(msg, NULL, 0, 0, PM_REMOVE);

				//入力システム更新処理
				Input::Update();

				if (MessageExit)
				{
					//間接的にウィンドウプロシージャを呼ぶ
					DispatchMessage(msg);

					//アプリ終了命令
					if (msg->message == WM_QUIT)
					{
						//終了
						LoadScene(EXIT_NUM_SCENE);
					}
				}
				else
				{
					//== ゲームループ ==//

					//時間更新処理
					Time::UpdateTime();

					//シーンの更新処理
					p_Scene->Update();

					//終了ではなければ
					if (SceneMode != EXIT_NUM_SCENE)
					{
						//描画開始
						D3D->Render_DrawBegin();

						//シーンの描画処理
						p_Scene->Draw();

						//ImGUIの描画
						ImGUIManager::Draw();

						//描画終了 ダブルバッファ切り替え
						D3D->Render_DrawEnd();
					}
				}

				LPARAM lp = 0;

				Input::SetMousePointer_HighResolution(lp);
			}
		}

		//シーンの解放
		delete p_Scene;


		//遷移先のシーンがEXITだったらループ終了
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