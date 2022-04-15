#pragma once

/*
ゲームの進行を行うクラス
*/
class Game
{
public:
	// コンストラクタ
	Game();
	// デストラクタ
	~Game() {};

	// 初期化処理
	// return true : 成功、false : 失敗
	bool Initialize();
	// ゲームループ
	void GameLoop();
	// 終了処理
	void Termination();

	// SDLが作るウィンドウ
	static SDL_Window* mWindow;

private:
	// 入力関連の処理
	void ProcessInput();
	// ゲームの更新処理
	void UpdateGame();
	// 描画関連の処理
	void GenerateOutput();
	// ロードしたデータの解放
	void UnloadData();

	// コアOpenGLプロファイル設定
	void OpenGLSetup();

	// ウィンドウの横幅
	const int MWidth;
	// ウィンドウの縦幅
	const int MHeight;

	// コンテクスト
	SDL_GLContext mContext;

	// 現在のシーン
	SceneBase* mNowScene;
	// ひとつ前のシーン
	SceneBase* mTmpScene;

	//FPS計測クラス
	FPS* mFps;

	// 入力管理クラス
	InputSystem* mInputSystem;

	// ゲームを続行するかどうか
	bool mIsRunningFlag;

	// ゲッター、セッター
public:
	// 最初のシーンをセット
	void SetFirstScene(SceneBase* _firstScene) { mNowScene = _firstScene; }
};

