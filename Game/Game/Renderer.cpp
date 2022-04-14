#include "pch.h"

// ���g�̃C���X�^���X�̏�����
Renderer* Renderer::mRenderer = nullptr;

Renderer::Renderer()
	: mSdlRenderer(nullptr)
{
}

SDL_Texture* Renderer::GetTexture(const string& _fileName)
{
	SDL_Texture* texture = nullptr;
	// ���łɍ쐬����Ă��Ȃ������ׂ�
	auto itr = mTextures.find(_fileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	// �쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
	else
	{
		if (TEXTURE->Load(_fileName))
		{
			// mTextures�ɗv�f���\�z
			mTextures.emplace(_fileName, texture);
		}
		// �e�N�X�`���̓ǂݍ��݂��o���Ȃ�������
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

void Renderer::CreateInstance()
{
	if (mRenderer == nullptr)
	{
		// �C���X�^���X�𐶐�
		mRenderer = new Renderer();
	}
}

void Renderer::DeleteInstance()
{
	if (mRenderer != nullptr)
	{
		// �폜
		delete mRenderer;
		mRenderer = nullptr;
	}
}

bool Renderer::Initialize()
{
	// SDL_Renderer�����
	// �`��ΏۂƂȂ�E�B���h�E�A-1�A
	mSdlRenderer = SDL_CreateRenderer(Game::mWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mSdlRenderer)
	{
		printf("SDLRenderer�̍쐬�Ɏ��s : %s", SDL_GetError());
		return false;
	}
	return true;
}

void Renderer::Draw()
{
	//@@@(�ݒ肵�Ȃ������獕�ɂȂ�)
	// �N���A�J���[���D���Ȃ悤�ɐݒ�
	glClearColor(0.2f, 0.0f, 0.4f, 0.5f);
	// �J���[�o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT);

	// @@@
	// �V�[����`��

	// �o�b�t�@�������A����ŃV�[�����\�������
	SDL_GL_SwapWindow(Game::mWindow);
}

void Renderer::UnloadData()
{
}

void Renderer::Termination()
{
	SDL_DestroyRenderer(mSdlRenderer);
	SDL_DestroyWindow(Game::mWindow);
}
