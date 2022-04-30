#include "pch.h"

// �����_���[���̂ւ̃|�C���^��`
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
	mRenderer->mSdlRenderer = SDL_CreateRenderer(Game::mWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer->mSdlRenderer)
	{
		printf("SDLRenderer�̍쐬�Ɏ��s : %s", SDL_GetError());
		return false;
	}

	// �V�F�[�_�[�̃��[�h
	if (!mRenderer->LoadShaders())
	{
		SDL_Log("�V�F�[�_�[�̃��[�h�Ɏ��s���܂���");
		return false;
	}

	// �X�v���C�g�p�̒��_�z����쐬
	mRenderer->CreateSpriteVerts();

	return true;
}

void Renderer::Draw()
{
	//@@@(�ݒ肵�Ȃ������獕�ɂȂ�)
	// �N���A�J���[���D���Ȃ悤�ɐݒ�
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
	// �J���[�o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT);

	// mSprites�̒��Ƀf�[�^�������
	if (mRenderer->mSprites.size() != 0)
	{
		// �X�v���C�g�̕`��
		mRenderer->SpriteDraw();
	}

	// �o�b�t�@�������A����ŃV�[�����\�������
	SDL_GL_SwapWindow(Game::mWindow);
}

void Renderer::SpriteDraw()
{
	// Sprite�̕`��B���u�����h��L���ɂ���
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,             // srcFactor��srcAlpha
		GL_ONE_MINUS_SRC_ALPHA);  // dstFactor��(1-srcAlpha)

	// �X�v���C�g�V�F�[�_�[���A�N�e�B�u�ɂ���
	// �X�v���C�g���_�z���L���ɂ���
	mRenderer->mSpriteShader->SetActive();
	mRenderer->mSpriteVerts->SetActive();
	// �S�ẴX�v���C�g�̕`��
	for (auto sprite : mRenderer->mSprites)
	{
		sprite->Draw(mRenderer->mSpriteShader);
	}
}

bool Renderer::LoadShaders()
{
	// �X�v���C�g�V�F�[�_�[�̐���
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// �r���[�ˉe�s����쐬���A�ݒ�
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(Game::MWidth, Game::MHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

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
	auto iter = find(mRenderer->mSprites.begin(), mRenderer->mSprites.end(), _spriteComponent);
	mRenderer->mSprites.erase(iter);
}

Texture* Renderer::GetTexture(const string& _fileName)
{
	Texture* texture = nullptr;

	// ���łɍ쐬����Ă��Ȃ������ׂ�
	auto itr = mTextures.find(_fileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	// �쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
	else
	{
		texture = new Texture();
		if (texture->Load(_fileName))
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

Mesh* Renderer::GetMesh(const string& _fileName)
{
	return nullptr;
}

void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// �\�[�g�ς݂̔z��ő}���_��������
	// (DrawOrder�����������Ԃɕ`�悷�邽��)
	int myDrawOrder = _spriteComponent->GetDrawOrder();
	auto iter = mRenderer->mSprites.begin();
	for (;
		iter != mRenderer->mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// �C�e���[�^�\�̈ʒu�̑O�ɗv�f��}������
	mRenderer->mSprites.insert(iter, _spriteComponent);
}

void Renderer::Termination()
{
	delete mRenderer->mSpriteVerts;

	mRenderer->mSpriteShader->Unload();
	delete mRenderer->mSpriteShader;

	SDL_DestroyRenderer(mRenderer->mSdlRenderer);
	SDL_DestroyWindow(Game::mWindow);
}


void Renderer::UnloadData()
{
	
}