#include "pch.h"

// ���g�̃C���X�^���X�̏�����
ActorManager* ActorManager::mManager = nullptr;

ActorManager::ActorManager()
	: mUpdatingActor(false)
{
}

void ActorManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		// �C���X�^���X�𐶐�
		mManager = new ActorManager();
	}
}

void ActorManager::DeleteInstance()
{
	if (mManager != nullptr)
	{
		// �폜
		delete mManager;
		mManager = nullptr;
	}
}

void ActorManager::AddActor(Actor* _actor)
{
	// �A�N�^�[�̍X�V���Ȃ�҂��ɒǉ�
	if (mManager->mUpdatingActor)
	{
		mManager->mPendingActors.emplace_back(_actor);
	}
	else
	{
		mManager->mActors.emplace_back(_actor);
	}
}

void ActorManager::RemoveActor()
{
	// �����A�N�^�[�𔻕�
	vector<Actor*> deleteActors;
	for (auto actor : mManager->mActors)
	{
		// ���̃A�N�^�[���������ꂽ�V�[���ƌ��݂̃V�[�����قȂ��
		if (actor->GetScene() != SceneBase::mIsScene)
		{
			deleteActors.emplace_back(actor);
		}
	}
	// �A�N�^�[������(mActors����폜�����)
	for (auto actor : deleteActors)
	{
		delete actor;
	}

	//// mActors�̗v�f��0����Ȃ�������
	//while (!mActors.empty())
	//{
	//	// �Ō�̗v�f������
	//	delete mActors.back();
	//}

	// @@@ ha??
	//// mPendingObjects����_actor��T���Aactor�ɑ��
	//auto actor = find(mPendingActors.begin(), mPendingActors.end(), _actor);
	//// actor�������v�f�̎����w���C�e���[�^����Ȃ�������
	//if (actor != mPendingActors.end())
	//{
	//	// actor�Ɩ����v�f�����ւ���
	//	iter_swap(actor, mPendingActors.end() - 1);
	//	// �����v�f���폜����
	//	mPendingActors.pop_back();
	//}

	//// mActorObjects�������悤�ɍ폜����
	//actor = find(mActors.begin(), mActors.end(), _actor);
	//if (actor != mActors.end())
	//{
	//	iter_swap(actor, mActors.end() - 1);
	//	mActors.pop_back();
	//}
}

void ActorManager::ProcessInput(const InputState& _state)
{
	for (auto actor : mManager->mActors)
	{
		// �e���͊֐��ɓ��͏�Ԃ�n��
		actor->ProcessInput(_state);
	}
}

void ActorManager::UpdateActor(float _deltaTime)
{
	mManager->mUpdatingActor = true;

	for (auto actor : mManager->mActors)
	{
		// �e�A�N�^�[���X�V
		actor->Update(_deltaTime);
	}

	mManager->mUpdatingActor = false;

	// �҂��ɂȂ��Ă����A�N�^�[��mActorObjects�Ɉړ�
	for (auto pending : mManager->mPendingActors)
	{
		mManager->mActors.emplace_back(pending);
	}

	// �҂��̗v�f���폜
	mManager->mPendingActors.clear();

	// ���񂾃A�N�^�[���ꎞ�z��ɒǉ�
	vector<Actor*> deadActors;
	for (auto actor : mManager->mActors)
	{
		if (actor->GetState() == Actor::State::eDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	// ���񂾃A�N�^�[������(mActors����폜�����)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

// @@@ ha??
//void ActorManager::RemoveSceneActor(SceneBase::Scene _scene)
//{
//	// mActorObjects�̗v�f��0����Ȃ�������
//	while (!mActors.empty())
//	{
//		// �Ō�̗v�f������
//		delete mActors.back();
//	}
//}