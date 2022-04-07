#include "pch.h"

int main(int argc, char** argv)
{
	// ゲームクラスの定義
	Game game;
	// ゲームクラスの初期化が成功したか
	bool success = game.Initialize();
	
	if (success)
	{
		game.GameLoop();
	}

	// ゲームクラスの終了処理
	game.Termination();

	return 0;
}