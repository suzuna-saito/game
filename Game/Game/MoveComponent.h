#pragma once

/*
�A�N�^�[�𓮂����N���X
*/
class MoveComponent :public Component
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����A�N�^�[�̃|�C���^</param>
	/// <param name="_updateOrder">�X�V�����B�l���������قǐ�ɍX�V�����</param>
	MoveComponent(class Actor* _owner,int _updateOrder = 10);
	// �f�X�g���N�^
	~MoveComponent() {};

	// �X�V����
	void Update(float _deltaTime) override;

private:
	// ��]���x
	float mAngularSpeed;
	// �ړ����x
	float mMoveSpeed;

public:  // �Q�b�^�[�B�Z�b�^�[
	// ��]���x���擾����
	float GetAngularSpeed()const { return mAngularSpeed; }
	// �ړ����x���擾����
	float GetMoveSpeed()const { return mMoveSpeed; }

	// ��]���x���Z�b�g����
	void SetAngularSpeed(float _speed) { mAngularSpeed = _speed; }
	// �ړ����x���Z�b�g����
	void SetMoveSpeed(float _speed) { mMoveSpeed = _speed; }
};

