#pragma once

/*
�S�Ă�Actor�̊��N���X
*/
class Actor
{
public:
	// �A�N�^�[�̏�ԊǗ��p�^�O
	enum class State :unsigned char
	{
		// �A�N�e�B�u
		eActive,
		// �X�V��~
		ePaused,
		// �X�V�I��
		eDead,
	};

	// �A�N�^�[�̎�ޔ��ʃ^�O
	enum class Tag :unsigned char
	{
		// ��
		eGround,
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_nowScene">�������ꂽ���̃V�[��</param>
	/// <param name="_actorTag">�A�N�^�[�̃^�O</param>
	Actor(const SceneBase::Scene& _nowScene, const Tag& _actorTag);
	// �f�X�g���N�^
	virtual ~Actor() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void Update(float _deltaTime);

	/// <summary>
	/// �A�N�^�[�����S�R���|�[�l���g���X�V
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateComponents(float _deltaTime);

	/// <summary>
	/// ���͏�Ԃ��󂯎��Actor��Component�̓��͍X�V�֐����Ăяo��
	/// </summary>
	/// <param name="_keyState">�e���͋@��̓��͏��</param>
	void ProcessInput(const InputState& _keyState);

	/// <summary>
	/// �A�N�^�[�Ǝ��̓��͏���ϐ��ɕۑ���UpdateActor�ōX�V���s��
	/// </summary>
	/// <param name="_keyState">�e���͋@��̓��͏��</param>
	virtual void ActorInput(const InputState& _keyState) {};

	/// <summary>
	/// �A�N�^�[�Ǝ��̍X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	virtual void UpdateActor(float _deltaTime) = 0;

	// �X�̕ϊ��s����쐬
	void ComputeWorldTransform();

protected:
	// �e���̃A�N�^�[�̏��
	State mState;

	// @@@
	// Transform
	Vector3 mPos;
	Vector3 mScale;
	Quaternion mRotation;

	// �A�N�^�[�̃��[���h�s��
	Matrix4 mWorldTransform;
	// ���[���h�s��̍Čv�Z�̕K�v�����Ǘ�
	bool mRecomputeWorldTransform;

	// �e���̃A�N�^�[�����R���|�[�l���g
	vector<Component*>mComponents;

private:
	// �e���̃A�N�^�[�𐶐������V�[��
	SceneBase::Scene mDirthplaceScene;
	// �e���̃A�N�^�[�����^�O
	Tag mTag;

public:  // �Q�b�^�[�A�Z�b�^�[
	// �A�N�^�[���������ꂽ���̃V�[�����擾
	SceneBase::Scene GetScene()const { return mDirthplaceScene; }

	// �A�N�^�[�̏�Ԃ��擾
	State GetState()const { return mState; }

	// �A�N�^�[�̃|�W�V�������擾
	const Vector3& GetPosition()const { return mPos; }
	// �A�N�^�[�̌������擾
	const Quaternion& GetRotation()const { return mRotation; }

	// �A�N�^�[�̃��[���h�s����擾
	const Matrix4& GetWorldTransform()const { return mWorldTransform; }

	// �A�N�^�[�̑O����\���x�N�g�����擾
	Vector3 GetForward()const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	// �A�N�^�[�̃|�W�V�������Z�b�g(mRecomputeWorldTransform��true�ɂ���)
	void SetPosition(const Vector3& _pos) { mPos = _pos; mRecomputeWorldTransform = true; }
	// �A�N�^�[�̌������Z�b�g(mRecomputeWorldTransform��true�ɂ���)
	void SetRotation(const Quaternion& _qotation) { mRotation = _qotation; mRecomputeWorldTransform = true; }
};

