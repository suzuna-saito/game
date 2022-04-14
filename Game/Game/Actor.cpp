#include "pch.h"

Actor::Actor(const SceneBase::Scene& _nowScene, const Tag& _actorTag)
	: mState(State::eActive)
	, mDirthplaceScene(_nowScene)
	, mTag(_actorTag)
{
	// アクターを追加する
	ACTOR_MANAGER->AddActor(this);
}

void Actor::Update(float _deltaTime)
{
	// アクターの状態がアクティブだったら
	if (mState == State::eActive)
	{
		// アクター独自の更新
		UpdateActor(_deltaTime);
		// アクターがもつ全コンポーネントの更新
		UpdateComponents(_deltaTime);
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
