#include "pch.h"

Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{
}

bool Texture::Load(const string& _fileName)
{
	// �`�����l�������i�[���郍�[�J���ϐ�
	int channels = 0;

	// �t�@�C������摜�����[�h
	SDL_Surface* surf = IMG_Load(_fileName.c_str());
	if (!surf)
	{
		printf("�e�N�X�`���̓ǂݍ��݂Ɏ��s : %s", _fileName.c_str());
		return false;
	}

	// �摜�̕��A�����A�`�����l�������擾
	mWidth = surf->w;
	mHeight = surf->h;
	channels = surf->format->BytesPerPixel;

	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}

	// OpenGL�e�N�X�`���I�u�W�F�N�g���쐬(mTextureID�ɕۑ�)
	glGenTextures(1, &mTextureID);
	// �e�N�X�`�����A�N�e�B�u�ɂ���
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// �摜�f�[�^��OpenGL�ɃR�s�[����
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, surf->pixels);

	// SDL�T�[�t�F�X�͕s�v�Ȃ̂ŉ�����Ă���
	SDL_FreeSurface(surf);

	// �o�C���j�A�t�B���^��L���ɂ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}
