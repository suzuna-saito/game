#include "pch.h"

// ���g�̃C���X�^���X�̏�����
Renderer* Renderer::mRenderer = nullptr;

Renderer::Renderer()
	: mSdlRenderer(nullptr)
	, mSpriteVerts(nullptr)
	, mSpriteShader(nullptr)
{
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

	// �V�F�[�_�[�̃��[�h
	if (!LoadShaders())
	{
		SDL_Log("�V�F�[�_�[�̃��[�h�Ɏ��s���܂���");
		return false;
	}

	// �X�v���C�g�p�̒��_�z����쐬
	CreateSpriteVerts();

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

bool Renderer::LoadShaders()
{
	// �X�v���C�g�V�F�[�_�[�̐���
	mSpriteShader = new Shader();
	// @@@ �V�F�[�_�[�̖��O�ύX���邩���H
	if (!mSpriteShader->Load("Shaders/BasicMesh.vert", "Shaders/BasicMesh.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();

	return true;
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

void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = find(mSprites.begin(), mSprites.end(), _spriteComponent);
	mSprites.erase(iter);
}

SDL_Texture* Renderer::GetTexture(const string& _fileName)
{
	Texture* texture = nullptr;

	// ���݂̗v�f
	SDL_Texture* nowTexture = nullptr;
	// ���łɍ쐬����Ă��Ȃ������ׂ�
	auto itr = mTextures.find(_fileName);
	if (itr != mTextures.end())
	{
		nowTexture = itr->second;
	}
	// �쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
	else
	{
		texture = new Texture();
		if (texture->Load(_fileName))
		{
			// mTextures�ɗv�f���\�z
			mTextures.emplace(_fileName, nowTexture);
		}
		// �e�N�X�`���̓ǂݍ��݂��o���Ȃ�������
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return nowTexture;
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

void Renderer::Termination()
{
	SDL_DestroyRenderer(mSdlRenderer);
	SDL_DestroyWindow(Game::mWindow);
}