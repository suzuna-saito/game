#include "pch.h"

//�R���g���[���[���ڑ����ꂽ���̃t���O�̏�����
bool InputSystem::mControllerConnected = false;

bool InputSystem::Initialize()
{
	// �L�[�{�[�h�̏���������
	// ���݂̃L�[�{�[�h�̏��
	mState.m_keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	// 1�t���[���O�̓��͏�Ԃ�������
	memset(mState.m_keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

	// @@@
	// �p�b�h�̐ݒ�t�@�C���@gamecontrollerdb.txt�@�̓ǂݍ��݂Ɩ�肪�������̃`�F�b�N
	int iNumOfControllers = SDL_GameControllerAddMappingsFromFile("Assets/Config/GameControllerdb.txt");
	if (iNumOfControllers == -1)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Error loading database [%s]", SDL_GetError());
		return false;
	}

	// @@@
	// �R���g���[���[���J��

	// @@@
	// �R���g���[���[�C�x���g�̖����i�����炩��t���[�����ɏ�Ԃ��擾���邽�߁j

	return true;
}

void InputSystem::PrepareForUpdate()
{
	//���݂̓��͏�Ԃ��P�t���[���O�̓��͏�ԂɃR�s�[����
	//�L�[�{�[�h
	memcpy(mState.m_keyboard.mPrevState,
		mState.m_keyboard.mCurrState,
		SDL_NUM_SCANCODES);

	// @@@
	// �R���g���[���[
}

void InputSystem::Update()
{
	// @@@
	// �R���g���[���[

}

void InputSystem::Termination()
{
	// @@@
	// �R���g���[���[����������
}

const bool KeyboardState::GetKeyValue(SDL_Scancode _keyCode) const
{
	return mCurrState[_keyCode] == 1;
}

const bool KeyboardState::GetKeyDownValue(SDL_Scancode _keyCode) const
{
	if (mPrevState[_keyCode] == 0 && mCurrState[_keyCode] == 1)
	{
		return true;
	}
	return false;
}

const ButtonState KeyboardState::GetKeyState(SDL_Scancode _keyCode) const
{
	if (mPrevState[_keyCode] == 0)
	{
		if (mCurrState[_keyCode] == 0)
		{
			return ButtonState::eNone;
		}
		else
		{
			return ButtonState::ePressed;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrState[_keyCode] == 0)
		{
			return ButtonState::eReleased;
		}
		else
		{
			return ButtonState::eHeld;
		}
	}
}
