#include "pch.h"

Game::Game()
	: mIsRunningFlag(false)
	, mFps(nullptr)
	, mInputSystem(nullptr)
	, mWindow(nullptr)
	, mContext(nullptr)
	, MWidth(1920)
	, MHeight(1080)
{
}

bool Game::Initialize()
{
	// SDL�̏�����
	// �Ԃ�l�̐�����0�łȂ�������
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | 
		SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) != 0)
	{
		SDL_Log("SDL���������ł��܂��� : %s", SDL_GetError());
		return false;
	}

	// �E�B���h�E�̍쐬
	// �쐬�O�ɐF�[�x�Ȃǂ̑�����ݒ肷��
	OpenGLSetup();
	// �^�C�g���Ax���W�Ay���W�A���A�����A�t���O
	mWindow = SDL_CreateWindow("Game", 0, 0, MWidth, MHeight, SDL_WINDOW_OPENGL);
	// mWindow���Anullptr��������
	if (!mWindow)
	{
		SDL_Log("�E�B���h�E�̍쐬�Ɏ��s���܂��� : %s", SDL_GetError());
		return false;
	}

	// OpenGL�̃R���e�N�X�g���쐬
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEW�̏�����
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("GLEW�̏������Ɏ��s���܂���.");
		return false;
	}

	// �ꕔ�̃v���b�g�t�H�[���ŏo�閳�Q�ȃG���[�R�[�h���N���A����
	glGetError();

	return true;
}

void Game::GameLoop()
{
	while (mIsRunningFlag)
	{
		// ���͊֘A�̏���
		ProcessInput();

		// ���݂̃V�[���̓��͏���
		mNowScene->Input(mInputSystem->GetState());

		// ���݂̃V�[���̍X�V����
		mTmpScene = mNowScene->Update();

		// �V�[���̐؂�ւ������������H
		if (mTmpScene != mNowScene)
		{
			// ���݂̃V�[���̉��
			delete mNowScene;

			// ���ݎ��s���̃V�[���̐؂�ւ�
			mNowScene = mTmpScene;
			continue;
		}

		// �Q�[���̍X�V����
		UpdateGame();
		// ���݂̃V�[���̕`�揈��
		GenerateOutput();
		// FPS�̍X�V����
		mFps->Update();
	}
}

void Game::Termination()
{
	// �f�[�^�̃A�����[�h
	UnloadData();
	// @@@
	// �X�^�e�B�b�N�N���X�̉������

	// �N���X�̉������
	delete mFps;
	delete mInputSystem;

	// �T�u�V�X�e���̏I��
	SDL_Quit();
}

void Game::ProcessInput()
{
	mInputSystem->PrepareForUpdate();

	SDL_Event event;
	// �L���[�ɃC�x���g������ΌJ��Ԃ�
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunningFlag = false;
			break;
		default:
			break;
		}
	}

	mInputSystem->Update();

	// ���݂̏�Ԃ��i�[���ꂽ�z��
	const InputState& state = mInputSystem->GetState();

	// ESC�L�[���A@@@�R���g���[���[�̏I���������ꂽ��
	if (state.m_keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::eReleased)
	{
		mIsRunningFlag = false;
	}

	// @@@ ���͏�Ԃ̍X�V
}

void Game::UpdateGame()
{
	float deltaTime = mFps->GetDeltaTime();

	// @@@ �Q�[���̍X�V����
}

void Game::GenerateOutput()
{
	RENDERER->Draw();
}

void Game::UnloadData()
{
}

void Game::OpenGLSetup()
{
	// OpenGL�̊e������ݒ肷��
	// �R�AOpenGL�v���t�@�C�����g��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGL�̎g�p�o�[�W������3.3�Ɏw��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA�e�`�����l��8�r�b�g�̃J���[�o�b�t�@���g��
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// �_�u���o�b�t�@��L���ɂ���
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// �n�[�h�E�F�A�A�N�Z�����[�V�������g��
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}
