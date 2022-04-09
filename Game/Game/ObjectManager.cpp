#include "pch.h"

// ���g�̃C���X�^���X�̏�����
ObjectManager* ObjectManager::mManager = nullptr;

void ObjectManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		// �C���X�^���X�𐶐�
		mManager = new ObjectManager();
	}
}

void ObjectManager::DeleteInstance()
{
	if (mManager != nullptr)
	{
		// �폜
		delete mManager;
		mManager = nullptr;
	}
}

void ObjectManager::AddObject(Actor* _object)
{
	// mActorObjects�ɗv�f��ǉ�
	mActorObjects.emplace_back(_object);
}

void ObjectManager::ProcessInput(const InputState& _state)
{
	for (auto obj : mActorObjects)
	{
		// �e���͊֐��ɓ��͏�Ԃ�n��
		obj->ProcessInput(_state);
	}
}

void ObjectManager::UpdateObject(float _deltaTime)
{
	for (auto actorObject : mActorObjects)
	{
		// �e�I�u�W�F�N�g���X�V
		actorObject->Update(_deltaTime);
	}
}

void ObjectManager::RemoveObject(Actor* _object)
{
	// mActorObjects����_object��T���Aobj�ɑ��
	auto obj = find(mActorObjects.begin(), mActorObjects.end(), _object);

	// obj�������v�f�̎����w���C�e���[�^����Ȃ�������
	if (obj != mActorObjects.end())
	{
		// obj�Ɩ����v�f�����ւ���
		iter_swap(obj, mActorObjects.end() - 1);
		// �����v�f���폜����
		mActorObjects.pop_back();
	}
}

void ObjectManager::RemoveSceneObject()
{
	// mActorObjects�̗v�f��0����Ȃ�������
	while (!mActorObjects.empty())
	{
		// �Ō�̗v�f������
		delete mActorObjects.back();
	}
}

ObjectManager::ObjectManager()
{
}