#pragma once

// �O���錾
class Actor;

/*
�S�ẴR���|�[�l���g�̊Ǘ����s��
*/
class Component
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_updateOrder">�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����)</param>
	Component(Actor* _owner, int _updateOrder = 100);

	// �f�X�g���N�^
	virtual ~Component();

	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="_state">�e���͋@��̓��͏��</param>
	virtual void ProcessInput(const struct InputState& _state) {}

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	virtual void CmpUpdate(float _deltaTime) = 0;

protected:
	// �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃|�C���^
	Actor* mOwner;

	// �R���|�[�l���g�̍X�V����
	int mUpdateOrder;

	// �Q�b�^�[�A�Z�b�^�[
public:
	int GetUpdateOder() { return mUpdateOrder; }
};

