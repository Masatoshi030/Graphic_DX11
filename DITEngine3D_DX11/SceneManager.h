#pragma once

//=============================================================//
//	シーンマネージャーをシングルトンで管理するクラス
//=============================================================//

#include <Windows.h>

#include "Scene_Game.h"

enum SCENE_TYPE
{
	GAME_SCENE,			//ゲームシーン
	EXIT_NUM_SCENE,		//ゲーム終了シーンかつシーンの総数
};

#define SCENE_MANAGER SCENE_MANAGERSYSTEM::Get_Instance()

class SCENE_MANAGERSYSTEM
{
private:

	//プライベートコンストラクタ
	SCENE_MANAGERSYSTEM() {};

	//インスタンス
	static SCENE_MANAGERSYSTEM* Instance;

	//シーンを変更したかのフラグ
	bool bSceneChange = false;

	//今のシーンタイプ
	SCENE_TYPE SceneMode = GAME_SCENE;

	//今のシーンのポインタ
	Scene* p_Scene;

public:

	//======================================================
	//【SCENE_MANAGERクラスのゲッター】
	//・インスタンスが生成されていなければ作成
	static SCENE_MANAGERSYSTEM* Get_Instance()
	{
		//生成済みのインスタンスがなければ新規作成
		if (Instance == NULL)
		{
			Instance = new SCENE_MANAGERSYSTEM();
		}

		//インスタンスのポインターを返す
		return Instance;
	}

	//======================================================
	//ゲームメイン処理
	//msg：メッセージハンドルのポインター
	void Game_Main(MSG* msg);

	//======================================================
	//シーンをロードする
	//_Scene：遷移先のシーンタイプ
	void LoadScene(SCENE_TYPE _Scene);

	//======================================================
	//今のシーンを取得
	SCENE_TYPE Get_ActiveScene();
};