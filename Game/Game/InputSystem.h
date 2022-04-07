#pragma once

// ボタンの状態
enum class ButtonState :unsigned char
{
	// 押されていない
	eNone,
	// 押した
	ePressed,
	// 押されている
	eHeld,
	// 離した
	eReleased,
};

/*
キーボードの入力管理クラス
*/
class KeyboardState
{
public:
	// InputSystemから容易に更新できるようにする
	friend class InputSystem;
	
private:
	// 現在のキーボードの入力状態
	const Uint8* mCurrState;
	// 1フレーム前のキーボードの入力状態
	Uint8 mPrevState[SDL_NUM_SCANCODES];

	// ゲッター、セッター
public:
	/// <summary>
	/// 現在のキーの入力状態のみを取得する
	/// </summary>
	/// <param name="_keyCode">SDL_Scancodeのキーコード</param>
	/// <returns>true : 押されている 、false : 押されていない</returns>
	const bool GetKeyValue(SDL_Scancode _keyCode)const;

	/// <summary>
	/// 指定したキーが押されたタイミングを判定する
	/// </summary>
	/// <param name="_keyCode">SDL_Scancodeのキーコード</param>
	/// <returns>true : 押されている 、false : 押されていない</returns>
	const bool GetKeyDownValue(SDL_Scancode _keyCode) const;

	/// <summary>
	/// 現在と1フレーム前の状態からButtonStateを返す
	/// </summary>
	/// <param name="_keyCode">SDL_Scancodeのキーコード</param>
	/// <returns>ButtonState型の現在の状態</returns>
	const ButtonState GetKeyState(SDL_Scancode _keyCode) const;
};

// 各入力機器の入力状態をまとめたラッパー構造体
struct InputState
{
	// キーボード
	KeyboardState m_keyboard;
};

/*
入力情報を管理するクラス
*/
class InputSystem
{
public:

	// 初期化処理
	// return true : 成功、false : 失敗
	bool Initialize();

	// Updateの準備をする(SDL_PollEventsの直前に呼ぶ)
	void PrepareForUpdate();

	// 毎フレームの更新処理(SDL_PollEventsの直後に呼ぶ)
	void Update();

	// 終了処理
	void Termination();

private:
	// 各入力機器の入力状態をまとめたラッパー構造体
	InputState mState;
	// @@@
	// SDLでコントローラーを認識するためのクラスポインタ
	// @@@
	// コントローラーが接続されたか
	static bool mControllerConnected;

	// ゲッター、セッター
public:
	/// <summary>
	/// 現在の入力状態を取得する
	/// </summary>
	/// <returns>各入力情報をまとめた構造体(struct InputState)</returns>
	const InputState& GetState() const { return mState; }
	
	// @@@
	/// <summary>
	/// コントローラーが接続されたかを取得する
	/// </summary>
	/// <returns>true : された、false : されてない</returns>
	//static bool GetConnectedController() {return mComt}
};