#include "pch.h"

// ���g�̃C���X�^���X�̏�����
Texture* Texture::mTexture = nullptr;

Texture::Texture()
	: mTex(nullptr)
	, mWidth(0)
	, mHeight(0)
{
}

void Texture::CreateInstance()
{
	if (mTexture == nullptr)
	{
		// �C���X�^���X�𐶐�
		mTexture = new Texture();
	}
}

void Texture::DeleteInstance()
{
	if (mTexture != nullptr)
	{
		// �폜
		delete mTexture;
		mTexture = nullptr;
	}
}

bool Texture::Load(const string& _fileName)
{
	// �t�@�C������摜�����[�h
	SDL_Surface* surf = IMG_Load(_fileName.c_str());
	if (!surf)
	{
		printf("�e�N�X�`���̓ǂݍ��݂Ɏ��s : %s", _fileName.c_str());
		return false;
	}

	// Surface��Texture�ɕϊ�
	mTex = SDL_CreateTextureFromSurface(
		RENDERER->GetSDLRenderer(),	// ���p���郌���_���[
		surf);						// �ϊ�����surface
	if (!mTex)
	{
		printf("�T�[�t�F�X����e�N�X�`���̍쐬�Ɏ��s : %s", _fileName.c_str());
		return false;
	}

	// �摜�̕��A�������擾
	mWidth = surf->w;
	mHeight = surf->h;

	return true;
}
