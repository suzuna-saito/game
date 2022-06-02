#include "pch.h"

MoveComponent::MoveComponent(Actor* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mMoveSpeed(0.0f)
	, mAngularSpeed(0.0f)
{
}

void MoveComponent::Update(float _deltaTime)
{
	// 回転速度が0に近ければ向きを変更しない
	if (!Math::NearZero(mAngularSpeed))
	{
		Quaternion rot = mOwner->GetRotation();
		float angle = mAngularSpeed * _deltaTime;
		// 回転を追加させるクォータニオンを作成
		// (+z軸周りの回転)
		Quaternion inc(Vector3::UnitZ, angle);
		// もとのrotと増分のクォータニオンを結合
		rot = Quaternion::Concatenate(rot, inc);
		// 向きを更新
		mOwner->SetRotation(rot);
	}
	// 移動速度が0に近ければ位置を変更しない
	if (!Math::NearZero(mMoveSpeed))
	{
		Vector3 pos = mOwner->GetPosition();
		// アクターが向いている方向ベクトルに移動スピードを掛ける
		pos += mOwner->GetForward() * mMoveSpeed * _deltaTime;
		// ポジションを更新
		mOwner->SetPosition(pos);
	}
}
