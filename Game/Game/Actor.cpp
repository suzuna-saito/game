#include "pch.h"

Actor::Actor(const SceneBase::Scene& _nowScene, const Tag& _actorTag)
	: mState(State::eActive)
	, mDirthplaceScene(_nowScene)
	, mTag(_actorTag)
	, mPos(Vector3::Zero)
	, mScale(Vector3::Zero)
	, mRotation(Quaternion::Identity)
	, mWorldTransform(Matrix4::Identity)
	, mRecomputeWorldTransform(true)
{
	// アクターを追加する
	ActorManager::AddActor(this);
}

void Actor::Update(float _deltaTime)
{
	// アクターの状態がアクティブだったら
	if (mState == State::eActive)
	{
		// Transformのワールド変換
		ComputeWorldTransform();
		// アクター独自の更新
		UpdateActor(_deltaTime);
		// アクターがもつ全コンポーネントの更新
		UpdateComponents(_deltaTime);
		// Transformのワールド変換
		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float _deltaTime)
{
	for (auto cmp : mComponents)
	{
		// 各コンポーネントを更新
		cmp->CmpUpdate(_deltaTime);
	}
}

void Actor::ProcessInput(const InputState& _keyState)
{
	// アクターの状態がアクティブだったら
	if (mState == State::eActive)
	{
		for (auto cmp : mComponents)
		{
			// 各コンポーネントの入力処理
			cmp->ProcessInput(_keyState);
		}

		// 各アクターの入力処理
		ActorInput(_keyState);
	}
}

void Actor::ComputeWorldTransform()
{
	// ワールド変換が必要だったら
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		// スケールのワールド変換
		mWorldTransform = Matrix4::CreateScale(mScale);
		// 回転のワールド変換
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		// 平行移動のワールド変換
		mWorldTransform *= Matrix4::CreateTranslation(mPos);

		// ワールド変換の更新をコンポーネントに通知する
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}
