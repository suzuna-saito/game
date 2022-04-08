#pragma once

// �O���錾
class Component;

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

	// �R���X�g���N�^
	Actor();
	// �f�X�g���N�^
	virtual ~Actor();

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

private:
	// �A�N�^�[�̏��
	State mState;

	// �A�N�^�[�����R���|�[�l���g
	vector<Component*>mComponents;
};

