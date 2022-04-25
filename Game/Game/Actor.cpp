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
	// �A�N�^�[��ǉ�����
	ActorManager::AddActor(this);
}

void Actor::Update(float _deltaTime)
{
	// �A�N�^�[�̏�Ԃ��A�N�e�B�u��������
	if (mState == State::eActive)
	{
		// Transform�̃��[���h�ϊ�
		ComputeWorldTransform();
		// �A�N�^�[�Ǝ��̍X�V
		UpdateActor(_deltaTime);
		// �A�N�^�[�����S�R���|�[�l���g�̍X�V
		UpdateComponents(_deltaTime);
		// Transform�̃��[���h�ϊ�
		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float _deltaTime)
{
	for (auto cmp : mComponents)
	{
		// �e�R���|�[�l���g���X�V
		cmp->CmpUpdate(_deltaTime);
	}
}

void Actor::ProcessInput(const InputState& _keyState)
{
	// �A�N�^�[�̏�Ԃ��A�N�e�B�u��������
	if (mState == State::eActive)
	{
		for (auto cmp : mComponents)
		{
			// �e�R���|�[�l���g�̓��͏���
			cmp->ProcessInput(_keyState);
		}

		// �e�A�N�^�[�̓��͏���
		ActorInput(_keyState);
	}
}

void Actor::ComputeWorldTransform()
{
	// ���[���h�ϊ����K�v��������
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		// �X�P�[���̃��[���h�ϊ�
		mWorldTransform = Matrix4::CreateScale(mScale);
		// ��]�̃��[���h�ϊ�
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		// ���s�ړ��̃��[���h�ϊ�
		mWorldTransform *= Matrix4::CreateTranslation(mPos);

		// ���[���h�ϊ��̍X�V���R���|�[�l���g�ɒʒm����
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}
