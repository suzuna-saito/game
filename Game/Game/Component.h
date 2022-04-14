#pragma once

// 前方宣言
class Actor;

/*
全てのコンポーネントの管理を行う
*/
class Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするアクターのポインタ</param>
	/// <param name="_updateOrder">コンポーネントの更新順番（数値が小さいほど早く更新される)</param>
	Component(Actor* _owner, int _updateOrder = 100);

	// デストラクタ
	virtual ~Component();

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="_state">各入力機器の入力状態</param>
	virtual void ProcessInput(const struct InputState& _state) {}

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	virtual void CmpUpdate(float _deltaTime) = 0;

protected:
	// アタッチしているアクターのポインタ
	Actor* mOwner;

	// コンポーネントの更新順序
	int mUpdateOrder;

	// ゲッター、セッター
public:
	int GetUpdateOder() { return mUpdateOrder; }
};

