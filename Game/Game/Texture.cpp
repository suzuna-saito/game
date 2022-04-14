#include "pch.h"

// 自身のインスタンスの初期化
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
		// インスタンスを生成
		mTexture = new Texture();
	}
}

void Texture::DeleteInstance()
{
	if (mTexture != nullptr)
	{
		// 削除
		delete mTexture;
		mTexture = nullptr;
	}
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
