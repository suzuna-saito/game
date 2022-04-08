#pragma once

// 前方宣言
class Component;

/*
全てのActorの基底クラス
*/
class Actor
{
public:
	// アクターの状態管理用タグ
	enum class State :unsigned char
	{
		// アクティブ
		eActive,
		// 更新停止
		ePaused,
		// 更新終了
		eDead,
	};

	// コンストラクタ
	Actor();
	// デストラクタ
	virtual ~Actor();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void Update(float _deltaTime);

	/// <summary>
	/// アクターがもつ全コンポーネントを更新
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateComponents(float _deltaTime);

	/// <summary>
	/// 入力状態を受け取りActorとComponentの入力更新関数を呼び出す
	/// </summary>
	/// <param name="_keyState">各入力機器の入力状態</param>
	void ProcessInput(const InputState& _keyState);

	/// <summary>
	/// アクター独自の入力情報を変数に保存しUpdateActorで更新を行う
	/// </summary>
	/// <param name="_keyState">各入力機器の入力状態</param>
	virtual void ActorInput(const InputState& _keyState) {};

	/// <summary>
	/// アクター独自の更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	virtual void UpdateActor(float _deltaTime) = 0;

private:
	// アクターの状態
	State mState;

	// アクターが持つコンポーネント
	vector<Component*>mComponents;
};

