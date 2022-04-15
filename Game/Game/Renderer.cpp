#include "pch.h"

// ���g�̃C���X�^���X�̏�����
Renderer* Renderer::mRenderer = nullptr;

Renderer::Renderer()
	: mSdlRenderer(nullptr)
	, mSpriteVerts(nullptr)
{
}

void Renderer::CreateSpriteVerts()
{
	float vertices[] =
	{
		// x     y     z    nx   ny   nz    u    v
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // ���㒸�_
		 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // �E�㒸�_
		 0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // �E�����_
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // �������_
	};

	unsigned int indices[] =
	{
		0, 2, 1,
		2, 0, 3
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
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
	delete mSpriteVerts;
}

void Renderer::Termination()
{
	SDL_DestroyRenderer(mSdlRenderer);
	SDL_DestroyWindow(Game::mWindow);
}

void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// �\�[�g�ς݂̔z��ő}���_��������
	// (DrawOrder�����������Ԃɕ`�悷�邽��)
	int myDrawOrder = _spriteComponent->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// �C�e���[�^�\�̈ʒu�̑O�ɗv�f��}������
	mSprites.insert(iter, _spriteComponent);
}

void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = find(mSprites.begin(), mSprites.end(), _spriteComponent);
	mSprites.erase(iter);
}
