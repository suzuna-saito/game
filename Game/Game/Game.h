#pragma once

/*
�Q�[���̐i�s���s���N���X
*/
class Game
{
public:
	// �R���X�g���N�^
	Game();
	// �f�X�g���N�^
	~Game() {};

	// ����������
	// return true : �����Afalse : ���s
	bool Initialize();
	// �Q�[�����[�v
	void GameLoop();
	// �I������
	void Termination();

	// SDL�����E�B���h�E
	static SDL_Window* mWindow;
	// �E�B���h�E�̉���
	static const float MWidth;
	// �E�B���h�E�̏c��
	static const float MHeight;

private:
	// ���͊֘A�̏���
	void ProcessInput();
	// �Q�[���̍X�V����
	void UpdateGame();
	// ���[�h�����f�[�^�̉��
	void UnloadData();

	// �R�AOpenGL�v���t�@�C���ݒ�
	void OpenGLSetup();

	// �R���e�N�X�g
	SDL_GLContext mContext;

	// ���݂̃V�[��
	SceneBase* mNowScene;
	// �ЂƂO�̃V�[��
	SceneBase* mTmpScene;

	//FPS�v���N���X
	FPS* mFps;

	// ���͊Ǘ��N���X
	InputSystem* mInputSystem;

	// �Q�[���𑱍s���邩�ǂ���
	bool mIsRunningFlag;

public: // �Q�b�^�[�A�Z�b�^�[
	// �ŏ��̃V�[�����Z�b�g
	void SetFirstScene(SceneBase* _firstScene) { mNowScene = _firstScene; }
};

