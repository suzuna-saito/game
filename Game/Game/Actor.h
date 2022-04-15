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

protected:
	// �e���̃A�N�^�[�𐶐������V�[��
	SceneBase::Scene mDirthplaceScene;
	// �e���̃A�N�^�[�̏��
	State mState;
	// �e���̃A�N�^�[�����^�O
	Tag mTag;

	// @@@
	// Transform


	// �e���̃A�N�^�[�����R���|�[�l���g
	vector<Component*>mComponents;

	// �Q�b�^�[�A�Z�b�^�[
public:
	// �A�N�^�[���������ꂽ���̃V�[�����擾
	SceneBase::Scene GetScene()const { return mDirthplaceScene; }
	// �A�N�^�[�̏�Ԃ��擾
	State GetState()const { return mState; }

};

