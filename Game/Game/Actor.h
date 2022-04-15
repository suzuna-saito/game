#pragma once

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

	// アクターの種類判別タグ
	enum class Tag :unsigned char
	{
		// 床
		eGround,
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_nowScene">生成された時のシーン</param>
	/// <param name="_actorTag">アクターのタグ</param>
	Actor(const SceneBase::Scene& _nowScene, const Tag& _actorTag);
	// デストラクタ
	virtual ~Actor() {};

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

protected:
	// 各自のアクターを生成したシーン
	SceneBase::Scene mDirthplaceScene;
	// 各自のアクターの状態
	State mState;
	// 各自のアクターが持つタグ
	Tag mTag;

	// @@@
	// Transform


	// 各自のアクターが持つコンポーネント
	vector<Component*>mComponents;

	// ゲッター、セッター
public:
	// アクターが生成された時のシーンを取得
	SceneBase::Scene GetScene()const { return mDirthplaceScene; }
	// アクターの状態を取得
	State GetState()const { return mState; }

};

