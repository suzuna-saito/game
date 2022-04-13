#include "pch.h"

// 自身のインスタンスの初期化
ActorManager* ActorManager::mManager = nullptr;

ActorManager::ActorManager()
	: mUpdatingActor(false)
{
}

void ActorManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		// インスタンスを生成
		mManager = new ActorManager();
	}
}

void ActorManager::DeleteInstance()
{
	if (mManager != nullptr)
	{
		// 削除
		delete mManager;
		mManager = nullptr;
	}
}

void ActorManager::AddActor(Actor* _actor)
{
	// アクターの更新中なら待ちに追加
	if (mUpdatingActor)
	{
		mPendingActors.emplace_back(_actor);
	}
	else
	{
		mActors.emplace_back(_actor);
	}
}

void ActorManager::RemoveActor()
{
	// 消すアクターを判別
	vector<Actor*> deleteActors;
	for (auto actor : mActors)
	{
		// このアクターが生成されたシーンと現在のシーンが異なれば
		if (actor->GetScene() != SceneBase::mIsScene)
		{
			deleteActors.emplace_back(actor);
		}
	}
	// アクターを消す(mActorsから削除される)
	for (auto actor : deleteActors)
	{
		delete actor;
	}

	//// mActorsの要素が0じゃなかったら
	//while (!mActors.empty())
	//{
	//	// 最後の要素を消す
	//	delete mActors.back();
	//}

	// @@@ ha??
	//// mPendingObjectsから_actorを探し、actorに代入
	//auto actor = find(mPendingActors.begin(), mPendingActors.end(), _actor);
	//// actorが末尾要素の次を指すイテレータじゃなかったら
	//if (actor != mPendingActors.end())
	//{
	//	// actorと末尾要素を入れ替える
	//	iter_swap(actor, mPendingActors.end() - 1);
	//	// 末尾要素を削除する
	//	mPendingActors.pop_back();
	//}

	//// mActorObjectsも同じように削除する
	//actor = find(mActors.begin(), mActors.end(), _actor);
	//if (actor != mActors.end())
	//{
	//	iter_swap(actor, mActors.end() - 1);
	//	mActors.pop_back();
	//}
}

void ActorManager::ProcessInput(const InputState& _state)
{
	for (auto actor : mActors)
	{
		// 各入力関数に入力状態を渡す
		actor->ProcessInput(_state);
	}
}

void ActorManager::UpdateActor(float _deltaTime)
{
	mUpdatingActor = true;

	for (auto actor : mActors)
	{
		// 各アクターを更新
		actor->Update(_deltaTime);
	}

	mUpdatingActor = false;

	// 待ちになっていたアクターをmActorObjectsに移動
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}

	// 待ちの要素を削除
	mPendingActors.clear();

	// 死んだアクターを一時配列に追加
	vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::State::eDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	// 死んだアクターを消す(mActorsから削除される)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

// @@@ ha??
//void ActorManager::RemoveSceneActor(SceneBase::Scene _scene)
//{
//	// mActorObjectsの要素が0じゃなかったら
//	while (!mActors.empty())
//	{
//		// 最後の要素を消す
//		delete mActors.back();
//	}
//}