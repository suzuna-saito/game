#include "pch.h"

Actor::Actor()
	: mState(State::eActive)
{
	// �I�u�W�F�N�g��ǉ�����
	OBJECT_MANAGER->AddObject(this);
}

Actor::~Actor()
{
	// �I�u�W�F�N�g���폜����
	OBJECT_MANAGER->RemoveObject(this);
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
