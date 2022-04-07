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

private:
	// ���͊֘A�̏���
	void ProcessInput();
	// �Q�[���̍X�V����
	void UpdateGame();
	// �`��֘A�̏���
	void GenerateOutput();
	// ���[�h�����f�[�^�̉��
	void UnloadData();

	// �R�AOpenGL�v���t�@�C���ݒ�
	void OpenGLSetup();
	// SDL�����E�B���h�E
	SDL_Window* mWindow;
	// �E�B���h�E�̉���
	const int MWidth;
	// �E�B���h�E�̏c��
	const int MHeight;
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

	// �Q�b�^�[�A�Z�b�^�[
public:
	// �ŏ��̃V�[�����Z�b�g
	// _firstScene �ŏ��̃V�[��
	void SetFirstScene(SceneBase* _firstScene) { mNowScene = _firstScene; }
};

