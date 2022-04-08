#include "pch.h"

int main(int argc, char** argv)
{
	// ゲームクラスの定義
	Game game;
	// ゲームクラスの初期化が成功したか
	bool success = game.Initialize();
	
	// 最初のシーンを設定
	game.SetFirstScene(new Title(SceneBase::Scene::eTitle));

	if (success)
	{
		game.GameLoop();
	}

	// ゲームクラスの終了処理
	game.Termination();

	return 0;
}