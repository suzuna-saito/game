#include "pch.h"

Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{
}

bool Texture::Load(const string& _fileName)
{
	// チャンネル数を格納するローカル変数
	int channels = 0;

	// ファイルから画像をロード
	SDL_Surface* surf = IMG_Load(_fileName.c_str());
	if (!surf)
	{
		printf("テクスチャの読み込みに失敗 : %s", _fileName.c_str());
		return false;
	}

	// 画像の幅、高さ、チャンネル数を取得
	mWidth = surf->w;
	mHeight = surf->h;
	channels = surf->format->BytesPerPixel;

	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}

	// OpenGLテクスチャオブジェクトを作成(mTextureIDに保存)
	glGenTextures(1, &mTextureID);
	// テクスチャをアクティブにする
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// 画像データをOpenGLにコピーする
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, surf->pixels);

	// SDLサーフェスは不要なので解放しておく
	SDL_FreeSurface(surf);

	// バイリニアフィルタを有効にする
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}
