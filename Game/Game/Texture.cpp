#include "pch.h"

Texture::Texture()
	: mTex(nullptr)
	, mWidth(0)
	, mHeight(0)
{
}

bool Texture::Load(const string& _fileName)
{
	// ファイルから画像をロード
	SDL_Surface* surf = IMG_Load(_fileName.c_str());
	if (!surf)
	{
		printf("テクスチャの読み込みに失敗 : %s", _fileName.c_str());
		return false;
	}

	// SurfaceをTextureに変換
	mTex = SDL_CreateTextureFromSurface(
		RENDERER->GetSDLRenderer(),	// 利用するレンダラー
		surf);						// 変換するsurface
	if (!mTex)
	{
		printf("サーフェスからテクスチャの作成に失敗 : %s", _fileName.c_str());
		return false;
	}

	// 画像の幅、高さを取得
	mWidth = surf->w;
	mHeight = surf->h;

	return true;
}
