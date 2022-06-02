#include "pch.h"

SDL_Window* Game::mWindow = nullptr;
const float Game::MWidth = 1920.0f;
const float Game::MHeight = 1080.0f;

Game::Game()
	: mIsRunningFlag(true)
	, mFps(nullptr)
	, mInputSystem(nullptr)
	, mContext(nullptr)
	, mNowScene(NULL)
	, mTmpScene(NULL)
{
}

bool Game::Initialize()
{
	// SDLの初期化
	// 返り値の整数が0でなかったら
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | 
		SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) != 0)
	{
		printf("SDLを初期化できません : %s", SDL_GetError());
		return false;
	}

	//入力管理クラスの初期化
	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize())
	{
		printf("インプットシステムの初期化に失敗しました");
		return false;
	}

	// ウィンドウの作成
	// 作成前に色深度などの属性を設定する
	OpenGLSetup();
	// タイトル、x座標、y座標、幅、高さ、フラグ
	mWindow = SDL_CreateWindow("Game", 0, 0, (int)MWidth, (int)MHeight, SDL_WINDOW_OPENGL);
	// mWindowが、nullptrだったら
	if (!mWindow)
	{
		printf("ウィンドウの作成に失敗しました : %s", SDL_GetError());
		return false;
	}

	// OpenGLのコンテクストを作成
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEWの初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEWの初期化に失敗しました.");
		return false;
	}

	// 一部のプラットフォームで出る無害なエラーコードをクリアする
	glGetError();

	// レンダラーの初期化
	Renderer::CreateInstance();
	if (!Renderer::Initialize())
	{
		printf("レンダラーの初期化に失敗しました\n");
		Renderer::DeleteInstance();
		return false;
	}

	// FPS管理クラスの初期化
	mFps = new FPS();

	// オブジェクト管理クラスの作成
	ActorManager::CreateInstance();
	// カメラクラスの作成
	Camera::CreateInstance();

	return true;
}

void Game::GameLoop()
{
	while (mIsRunningFlag)
	{
		// 入力関連の処理
		ProcessInput();

		// 現在のシーンの入力処理
		mNowScene->Input(mInputSystem->GetState());

		// 現在のシーンの更新処理
		mTmpScene = mNowScene->Update();

		// シーンの切り替えが発生した？
		if (mTmpScene != mNowScene)
		{
			// 現在のシーンの解放
			delete mNowScene;

			// いらないアクターを削除する
			ActorManager::RemoveActor();

			// 現在実行中のシーンの切り替え
			mNowScene = mTmpScene;
			continue;
		}

		// ゲームの更新処理
		UpdateGame();
		// 現在のシーンの描画処理
		Renderer::Draw();
		// FPSの更新処理
		mFps->Update();
	}
}

void Game::Termination()
{
	// データのアンロード
	UnloadData();

	// 実体を一つしか持たないクラスの解放処理
	Renderer::DeleteInstance();
	ActorManager::DeleteInstance();

	// クラスの解放処理
	delete mFps;
	delete mInputSystem;

	// サブシステムの終了
	SDL_Quit();
}

void Game::ProcessInput()
{
	mInputSystem->PrepareForUpdate();

	SDL_Event event;
	// キューにイベントがあれば繰り返す
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunningFlag = false;
			break;
		default:
			break;
		}
	}

	mInputSystem->Update();

	// 現在の状態が格納された配列
	const InputState& state = mInputSystem->GetState();

	//@@@ test eEndになったら
	// ESCキーか、@@@コントローラーの終了が押されたら
	if (state.m_keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::eReleased ||
		SceneBase::mIsScene == SceneBase::Scene::eEnd)
	{
		mIsRunningFlag = false;
	}

	// アクターの入力状態の更新
	ActorManager::ProcessInput(state);
}

void Game::UpdateGame()
{
	float deltaTime = mFps->GetDeltaTime();

	// アクターの更新処理
	ActorManager::UpdateActor(deltaTime);
}

void Game::UnloadData()
{
	//@@@
	// 描画しているデータを削除
	if (Renderer::mRenderer != nullptr)
	{
		Renderer::UnloadData();
		Renderer::Termination();
	}
}

void Game::OpenGLSetup()
{
	// OpenGLの各属性を設定する
	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGLの使用バージョンを3.3に指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA各チャンネル8ビットのカラーバッファを使う
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// ダブルバッファを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// ハードウェアアクセラレーションを使う
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}
