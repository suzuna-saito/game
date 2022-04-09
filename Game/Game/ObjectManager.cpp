#include "pch.h"

// 自身のインスタンスの初期化
ObjectManager* ObjectManager::mManager = nullptr;

void ObjectManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		// インスタンスを生成
		mManager = new ObjectManager();
	}
}

void ObjectManager::DeleteInstance()
{
	if (mManager != nullptr)
	{
		// 削除
		delete mManager;
		mManager = nullptr;
	}
}

void ObjectManager::AddObject(Actor* _object)
{
	// mActorObjectsに要素を追加
	mActorObjects.emplace_back(_object);
}

void ObjectManager::ProcessInput(const InputState& _state)
{
	for (auto obj : mActorObjects)
	{
		// 各入力関数に入力状態を渡す
		obj->ProcessInput(_state);
	}
}

void ObjectManager::UpdateObject(float _deltaTime)
{
	for (auto actorObject : mActorObjects)
	{
		// 各オブジェクトを更新
		actorObject->Update(_deltaTime);
	}
}

void ObjectManager::RemoveObject(Actor* _object)
{
	// mActorObjectsから_objectを探し、objに代入
	auto obj = find(mActorObjects.begin(), mActorObjects.end(), _object);

	// objが末尾要素の次を指すイテレータじゃなかったら
	if (obj != mActorObjects.end())
	{
		// objと末尾要素を入れ替える
		iter_swap(obj, mActorObjects.end() - 1);
		// 末尾要素を削除する
		mActorObjects.pop_back();
	}
}

void ObjectManager::RemoveSceneObject()
{
	// mActorObjectsの要素が0じゃなかったら
	while (!mActorObjects.empty())
	{
		// 最後の要素を消す
		delete mActorObjects.back();
	}
}

ObjectManager::ObjectManager()
{
}