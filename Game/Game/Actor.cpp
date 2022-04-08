#include "pch.h"

Actor::Actor()
	: mState(State::eActive)
{
	// オブジェクトを追加する
	OBJECT_MANAGER->AddObject(this);
}

Actor::~Actor()
{
	// オブジェクトを削除する
	OBJECT_MANAGER->RemoveObject(this);
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
