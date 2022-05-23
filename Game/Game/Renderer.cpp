#include "pch.h"

// �����_���[���̂ւ̃|�C���^��`
Renderer* Renderer::mRenderer = nullptr;

Renderer::Renderer()
	: mSdlRenderer(nullptr)
	, mSpriteVerts(nullptr)
	, mSpriteShader(nullptr)
	, mMeshShader(nullptr)
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
		printf("�V�F�[�_�[�̃��[�h�Ɏ��s���܂���\n");
		return false;
	}

	// �X�v���C�g�p�̒��_�z����쐬
	mRenderer->CreateSpriteVerts();

	return true;
}

void Renderer::Draw()
{
	//@@(�ݒ肵�Ȃ������獕�ɂȂ�)
	// �N���A�J���[���D���Ȃ悤�ɐݒ�
	/*glClearColor(1.0f, 1.0f, 1.0f, 0.5f);*/
	// �J���[�o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT);

	// Sprite�̕`��B���u�����h��L���ɂ���
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,             // srcFactor��srcAlpha
		GL_ONE_MINUS_SRC_ALPHA);  // dstFactor��(1-srcAlpha)

	// mSprites�̒��Ƀf�[�^�������
	if (mRenderer->mSprites.size() != 0)
	{
		// �X�v���C�g�̕`��
		mRenderer->SpriteDraw();
	}

	// �f�v�X�o�b�t�@�@�L�� / ���u�����f�B���O����
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	// ���b�V���R���|�[�l���g�̕`��
	// ��{�I�ȃ��b�V���V�F�[�_�[���A�N�e�B�u�ɂ���
	mRenderer->mMeshShader->SetActive();
	// �r���[�ˉe�s����X�V����
	mRenderer->mMeshShader->SetMatrixUniform("uViewProj", mRenderer->mView * mRenderer->mProjection);
	// @@@ �V�F�[�_�[�ɓn�����C�e�B���O�����X�V����
	// �S�Ẵ��b�V���̕`��
	for (auto mc : mRenderer->mMeshComponents)
	{
		mc->Draw(mRenderer->mMeshShader);
	}

	// �o�b�t�@�������A����ŃV�[�����\�������
	SDL_GL_SwapWindow(Game::mWindow);
}

void Renderer::SpriteDraw()
{
	// �X�v���C�g�V�F�[�_�[���A�N�e�B�u�ɂ���
	// �X�v���C�g���_�z���L���ɂ���
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	// �S�ẴX�v���C�g�̕`��
	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
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

	// @@@ ��œǂݎ��t�@�C���ς��Ƃ���
	// �W�����b�V���V�F�[�_�[�̍쐬
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

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

void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = find(mRenderer->mSprites.begin(), mRenderer->mSprites.end(), _spriteComponent);
	mRenderer->mSprites.erase(iter);
}

void Renderer::AddMeshComponent(MeshComponent* _meshComponent)
{
	// �X�P���g���f�[�^��p����ꍇ
	if (_meshComponent->GetIsSkeltal())
	{
		// �X�P���^�����b�V���R���|�[�l���g
	}
	else
	{
		mRenderer->mMeshComponents.emplace_back(_meshComponent);
	}
}

void Renderer::RemoveMeshcomponent(MeshComponent* _meshComponent)
{
	// �X�P���g���f�[�^��p����ꍇ
	if (_meshComponent->GetIsSkeltal())
	{
		// �X�P���^�����b�V���R���|�[�l���g
	}
	else
	{
		auto iter = find(mRenderer->mMeshComponents.begin(), mRenderer->mMeshComponents.end(),
			_meshComponent);
		mRenderer->mMeshComponents.erase(iter);
	}

}

Texture* Renderer::GetTexture(const string& _fileName)
{
	Texture* texture = nullptr;

	// ���łɍ쐬����Ă��Ȃ������ׂ�
	auto itr = mRenderer->mTextures.find(_fileName);
	if (itr != mRenderer->mTextures.end())
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
			mRenderer->mTextures.emplace(_fileName, texture);
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
	Mesh* m = nullptr;

	// ���łɍ쐬����Ă��Ȃ������ׂ�
	auto itr = mRenderer->mMeshes.find(_fileName);
	if (itr != mRenderer->mMeshes.end())
	{
		m = itr->second;
	}
	// �쐬�ς݂łȂ��ꍇ�A�V�������b�V�����쐬
	else
	{
		m = new Mesh();
		if (m->Load(_fileName, mRenderer))
		{
			mRenderer->mMeshes.emplace(_fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}

	return m;
}

void Renderer::Termination()
{
	delete mRenderer->mSpriteVerts;

	mRenderer->mSpriteShader->Unload();
	delete mRenderer->mSpriteShader;

	mRenderer->mMeshShader->Unload();
	delete mRenderer->mMeshShader;

	SDL_DestroyRenderer(mRenderer->mSdlRenderer);
	SDL_DestroyWindow(Game::mWindow);
}


void Renderer::UnloadData()
{
	
}