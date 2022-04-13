#include "pch.h"

Texture::Texture()
{
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
	SDL_Texture* tex = nullptr;
	tex = SDL_CreateTextureFromSurface(
		RENDERER->GetSDLRenderer(),	// ���p���郌���_���[
		surf);						// �ϊ�����surface
	if (!tex)
	{
		printf("�T�[�t�F�X����e�N�X�`���̍쐬�Ɏ��s : %s", _fileName.c_str());
		return false;
	}
	return true;
}
