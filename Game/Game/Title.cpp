#include "pch.h"

Title::Title(const Scene& _nowScene)
	: SceneBase()
{
	// ���݂̃V�[���^�O���X�V
	mIsScene = _nowScene;

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		mMapCreate->CreateGround();
	}
}

Title::~Title()
{
}

void Title::Input(const InputState& _state)
{
	// �X�y�[�X�L�[�������ꂽ��
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::ePressed)
	{
		// �J�ڃt���O���グ��
		mSceneTransitionFlag = true;
	}
}

SceneBase* Title::Update()
{
	// �J�ڃt���O���オ���Ă�����
	if (mSceneTransitionFlag)
	{
		//@@@
		// �e�X�g
		mIsScene = Scene::eEnd;
	}

	return this;
}