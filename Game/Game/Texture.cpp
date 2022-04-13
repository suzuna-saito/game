#include "pch.h"

Texture::Texture()
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
	SDL_Texture* tex = nullptr;
	tex = SDL_CreateTextureFromSurface(
		RENDERER->GetSDLRenderer(),	// 利用するレンダラー
		surf);						// 変換するsurface
	if (!tex)
	{
		printf("サーフェスからテクスチャの作成に失敗 : %s", _fileName.c_str());
		return false;
	}
	return true;
}
