#include "pch.h"

Title::Title(const Scene& _nowScene)
	: SceneBase()
{
	// 現在のシーンタグを更新
	mIsScene = _nowScene;

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		mMapCreate->CreateGround();
	}
}

Title::~Title()
{
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