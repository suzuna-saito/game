#pragma once

// �{�^���̏��
enum class ButtonState :unsigned char
{
	// ������Ă��Ȃ�
	eNone,
	// ������
	ePressed,
	// ������Ă���
	eHeld,
	// ������
	eReleased,
};

/*
�L�[�{�[�h�̓��͊Ǘ��N���X
*/
class KeyboardState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;
	
private:
	// ���݂̃L�[�{�[�h�̓��͏��
	const Uint8* mCurrState;
	// 1�t���[���O�̃L�[�{�[�h�̓��͏��
	Uint8 mPrevState[SDL_NUM_SCANCODES];

	// �Q�b�^�[�A�Z�b�^�[
public:
	/// <summary>
	/// ���݂̃L�[�̓��͏�Ԃ݂̂��擾����
	/// </summary>
	/// <param name="_keyCode">SDL_Scancode�̃L�[�R�[�h</param>
	/// <returns>true : ������Ă��� �Afalse : ������Ă��Ȃ�</returns>
	const bool GetKeyValue(SDL_Scancode _keyCode)const;

	/// <summary>
	/// �w�肵���L�[�������ꂽ�^�C�~���O�𔻒肷��
	/// </summary>
	/// <param name="_keyCode">SDL_Scancode�̃L�[�R�[�h</param>
	/// <returns>true : ������Ă��� �Afalse : ������Ă��Ȃ�</returns>
	const bool GetKeyDownValue(SDL_Scancode _keyCode) const;

	/// <summary>
	/// ���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	/// </summary>
	/// <param name="_keyCode">SDL_Scancode�̃L�[�R�[�h</param>
	/// <returns>ButtonState�^�̌��݂̏��</returns>
	const ButtonState GetKeyState(SDL_Scancode _keyCode) const;
};

// �e���͋@��̓��͏�Ԃ��܂Ƃ߂����b�p�[�\����
struct InputState
{
	// �L�[�{�[�h
	KeyboardState m_keyboard;
};

/*
���͏����Ǘ�����N���X
*/
class InputSystem
{
public:

	// ����������
	// return true : �����Afalse : ���s
	bool Initialize();

	// Update�̏���������(SDL_PollEvents�̒��O�ɌĂ�)
	void PrepareForUpdate();

	// ���t���[���̍X�V����(SDL_PollEvents�̒���ɌĂ�)
	void Update();

	// �I������
	void Termination();

private:
	// �e���͋@��̓��͏�Ԃ��܂Ƃ߂����b�p�[�\����
	InputState mState;
	// @@@
	// SDL�ŃR���g���[���[��F�����邽�߂̃N���X�|�C���^
	// @@@
	// �R���g���[���[���ڑ����ꂽ��
	static bool mControllerConnected;

	// �Q�b�^�[�A�Z�b�^�[
public:
	/// <summary>
	/// ���݂̓��͏�Ԃ��擾����
	/// </summary>
	/// <returns>�e���͏����܂Ƃ߂��\����(struct InputState)</returns>
	const InputState& GetState() const { return mState; }
	
	// @@@
	/// <summary>
	/// �R���g���[���[���ڑ����ꂽ�����擾����
	/// </summary>
	/// <returns>true : ���ꂽ�Afalse : ����ĂȂ�</returns>
	//static bool GetConnectedController() {return mComt}
};