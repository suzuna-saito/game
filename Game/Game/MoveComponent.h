#pragma once

/*
アクターを動かすクラス
*/
class MoveComponent :public Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするアクターのポインタ</param>
	/// <param name="_updateOrder">更新順序。値が小さいほど先に更新される</param>
	MoveComponent(class Actor* _owner,int _updateOrder = 10);
	// デストラクタ
	~MoveComponent() {};

	// 更新処理
	void Update(float _deltaTime) override;

private:
	// 回転速度
	float mAngularSpeed;
	// 移動速度
	float mMoveSpeed;

public:  // ゲッター。セッター
	// 回転速度を取得する
	float GetAngularSpeed()const { return mAngularSpeed; }
	// 移動速度を取得する
	float GetMoveSpeed()const { return mMoveSpeed; }

	// 回転速度をセットする
	void SetAngularSpeed(float _speed) { mAngularSpeed = _speed; }
	// 移動速度をセットする
	void SetMoveSpeed(float _speed) { mMoveSpeed = _speed; }
};

