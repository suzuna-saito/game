#include "pch.h"

//コントローラーが接続されたかのフラグの初期化
bool InputSystem::mControllerConnected = false;

bool InputSystem::Initialize()
{
	// キーボードの初期化処理
	// 現在のキーボードの状態
	mState.m_keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	// 1フレーム前の入力状態を初期化
	memset(mState.m_keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

	// @@@
	// パッドの設定ファイル　gamecontrollerdb.txt　の読み込みと問題が無いかのチェック
	int iNumOfControllers = SDL_GameControllerAddMappingsFromFile("Assets/Config/GameControllerdb.txt");
	if (iNumOfControllers == -1)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Error loading database [%s]", SDL_GetError());
		return false;
	}

	// @@@
	// コントローラーを開く

	// @@@
	// コントローラーイベントの無視（こちらからフレーム毎に状態を取得するため）

	return true;
}

void InputSystem::PrepareForUpdate()
{
	//現在の入力状態を１フレーム前の入力状態にコピーする
	//キーボード
	memcpy(mState.m_keyboard.mPrevState,
		mState.m_keyboard.mCurrState,
		SDL_NUM_SCANCODES);

	// @@@
	// コントローラー
}

void InputSystem::Update()
{
	// @@@
	// コントローラー

}

void InputSystem::Termination()
{
	// @@@
	// コントローラーがあったら
}

const bool KeyboardState::GetKeyValue(SDL_Scancode _keyCode) const
{
	return mCurrState[_keyCode] == 1;
}

const bool KeyboardState::GetKeyDownValue(SDL_Scancode _keyCode) const
{
	if (mPrevState[_keyCode] == 0 && mCurrState[_keyCode] == 1)
	{
		return true;
	}
	return false;
}

const ButtonState KeyboardState::GetKeyState(SDL_Scancode _keyCode) const
{
	if (mPrevState[_keyCode] == 0)
	{
		if (mCurrState[_keyCode] == 0)
		{
			return ButtonState::eNone;
		}
		else
		{
			return ButtonState::ePressed;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrState[_keyCode] == 0)
		{
			return ButtonState::eReleased;
		}
		else
		{
			return ButtonState::eHeld;
		}
	}
}
