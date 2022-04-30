#include "pch.h"

MoveComponent::MoveComponent(Actor* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mMoveSpeed(0.0f)
	, mAngularSpeed(0.0f)
{
}

void MoveComponent::Update(float _deltaTime)
{
	// ��]���x��0�ɋ߂���Ό�����ύX���Ȃ�
	if (!Math::NearZero(mAngularSpeed))
	{
		Quaternion rot = mOwner->GetRotation();
		float angle = mAngularSpeed * _deltaTime;
		// ��]��ǉ�������N�H�[�^�j�I�����쐬
		// (+z������̉�])
		Quaternion inc(Vector3::UnitZ, angle);
		// ���Ƃ�rot�Ƒ����̃N�H�[�^�j�I��������
		rot = Quaternion::Concatenate(rot, inc);
		// �������X�V
		mOwner->SetRotation(rot);
	}
	// �ړ����x��0�ɋ߂���Έʒu��ύX���Ȃ�
	if (!Math::NearZero(mMoveSpeed))
	{
		Vector3 pos = mOwner->GetPosition();
		// �A�N�^�[�������Ă�������x�N�g���Ɉړ��X�s�[�h���|����
		pos += mOwner->GetForward() * mMoveSpeed * _deltaTime;
		// �|�W�V�������X�V
		mOwner->SetPosition(pos);
	}
}
