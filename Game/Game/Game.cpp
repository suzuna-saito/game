#include "pch.h"

SDL_Window* Game::mWindow = nullptr;
const float Game::MWidth = 1920.0f;
const float Game::MHeight = 1080.0f;

Game::Game()
	: mIsRunningFlag(true)
	, mFps(nullptr)
	, mInputSystem(nullptr)
	, mContext(nullptr)
	, mNowScene(NULL)
	, mTmpScene(NULL)
{
}

bool Game::Initialize()
{
	// SDL�̏�����
	// �Ԃ�l�̐�����0�łȂ�������
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | 
		SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) != 0)
	{
		printf("SDL���������ł��܂��� : %s", SDL_GetError());
		return false;
	}

	//���͊Ǘ��N���X�̏�����
	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize())
	{
		printf("�C���v�b�g�V�X�e���̏������Ɏ��s���܂���");
		return false;
	}

	// �E�B���h�E�̍쐬
	// �쐬�O�ɐF�[�x�Ȃǂ̑�����ݒ肷��
	OpenGLSetup();
	// �^�C�g���Ax���W�Ay���W�A���A�����A�t���O
	mWindow = SDL_CreateWindow("Game", 0, 0, (int)MWidth, (int)MHeight, SDL_WINDOW_OPENGL);
	// mWindow���Anullptr��������
	if (!mWindow)
	{
		printf("�E�B���h�E�̍쐬�Ɏ��s���܂��� : %s", SDL_GetError());
		return false;
	}

	// OpenGL�̃R���e�N�X�g���쐬
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEW�̏�����
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW�̏������Ɏ��s���܂���.");
		return false;
	}

	// �ꕔ�̃v���b�g�t�H�[���ŏo�閳�Q�ȃG���[�R�[�h���N���A����
	glGetError();

	// �����_���[�̏�����
	Renderer::CreateInstance();
	if (!Renderer::Initialize())
	{
		printf("�����_���[�̏������Ɏ��s���܂���\n");
		Renderer::DeleteInstance();
		return false;
	}

	// FPS�Ǘ��N���X�̏�����
	mFps = new FPS();

	// �I�u�W�F�N�g�Ǘ��N���X�̍쐬
	ActorManager::CreateInstance();
	// �J�����N���X�̍쐬
	Camera::CreateInstance();

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

			// ����Ȃ��A�N�^�[���폜����
			ActorManager::RemoveActor();

			// ���ݎ��s���̃V�[���̐؂�ւ�
			mNowScene = mTmpScene;
			continue;
		}

		// �Q�[���̍X�V����
		UpdateGame();
		// ���݂̃V�[���̕`�揈��
		Renderer::Draw();
		// FPS�̍X�V����
		mFps->Update();
	}
}

void Game::Termination()
{
	// �f�[�^�̃A�����[�h
	UnloadData();

	// ���̂�����������Ȃ��N���X�̉������
	Renderer::DeleteInstance();
	ActorManager::DeleteInstance();

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

	//@@@ test eEnd�ɂȂ�����
	// ESC�L�[���A@@@�R���g���[���[�̏I���������ꂽ��
	if (state.m_keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::eReleased ||
		SceneBase::mIsScene == SceneBase::Scene::eEnd)
	{
		mIsRunningFlag = false;
	}

	// �A�N�^�[�̓��͏�Ԃ̍X�V
	ActorManager::ProcessInput(state);
}

void Game::UpdateGame()
{
	float deltaTime = mFps->GetDeltaTime();

	// �A�N�^�[�̍X�V����
	ActorManager::UpdateActor(deltaTime);
}

void Game::UnloadData()
{
	//@@@
	// �`�悵�Ă���f�[�^���폜
	if (Renderer::mRenderer != nullptr)
	{
		Renderer::UnloadData();
		Renderer::Termination();
	}
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
