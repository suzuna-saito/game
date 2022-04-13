#include "pch.h"

Title::Title(const Scene& _nowScene)
	: SceneBase()
{
	// 現在のシーンタグを更新
	mIsScene = _nowScene;

	// タイトル
	printf("aaa\n");
}

Title::~Title()
{
	// 現在のシーンで生成された全てのアクターの削除
	//ACTOR_MANAGER->RemoveSceneActor(Scene::eTitle);
}

void Title::Input(const InputState& _state)
{
	// スペースキーが押されたら
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::ePressed)
	{
		// 遷移フラグを上げる
		mSceneTransitionFlag = true;
	}
}

SceneBase* Title::Update()
{
	// 遷移フラグが上がっていたら
	if (mSceneTransitionFlag)
	{
		//@@@
		// テスト
		mIsScene = Scene::eEnd;
	}

	return this;
}