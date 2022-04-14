#include "pch.h"

Actor::Actor(const SceneBase::Scene& _nowScene, const Tag& _actorTag)
	: mState(State::eActive)
	, mDirthplaceScene(_nowScene)
	, mTag(_actorTag)
{
	// �A�N�^�[��ǉ�����
	ACTOR_MANAGER->AddActor(this);
}

void Actor::Update(float _deltaTime)
{
	// �A�N�^�[�̏�Ԃ��A�N�e�B�u��������
	if (mState == State::eActive)
	{
		// �A�N�^�[�Ǝ��̍X�V
		UpdateActor(_deltaTime);
		// �A�N�^�[�����S�R���|�[�l���g�̍X�V
		UpdateComponents(_deltaTime);
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
