#include "pch.h"

// 自身のインスタンスの初期化
Renderer* Renderer::mRenderer = nullptr;

Renderer::Renderer()
	: mSdlRenderer(nullptr)
	, mSpriteVerts(nullptr)
{
}

void Renderer::CreateSpriteVerts()
{
	float vertices[] =
	{
		// x     y     z    nx   ny   nz    u    v
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 左上頂点
		 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 右上頂点
		 0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右下頂点
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // 左下頂点
	};

	unsigned int indices[] =
	{
		0, 2, 1,
		2, 0, 3
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

SDL_Texture* Renderer::GetTexture(const string& _fileName)
{
	SDL_Texture* texture = nullptr;
	// すでに作成されていないか調べる
	auto itr = mTextures.find(_fileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	// 作成済みでない場合、新しくテクスチャを作成
	else
	{
		if (TEXTURE->Load(_fileName))
		{
			// mTexturesに要素を構築
			mTextures.emplace(_fileName, texture);
		}
		// テクスチャの読み込みが出来なかったら
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

void Renderer::CreateInstance()
{
	if (mRenderer == nullptr)
	{
		// インスタンスを生成
		mRenderer = new Renderer();
	}
}

void Renderer::DeleteInstance()
{
	if (mRenderer != nullptr)
	{
		// 削除
		delete mRenderer;
		mRenderer = nullptr;
	}
}

bool Renderer::Initialize()
{
	// SDL_Rendererを作る
	// 描画対象となるウィンドウ、-1、
	mSdlRenderer = SDL_CreateRenderer(Game::mWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mSdlRenderer)
	{
		printf("SDLRendererの作成に失敗 : %s", SDL_GetError());
		return false;
	}
	return true;
}

void Renderer::Draw()
{
	//@@@(設定しなかったら黒になる)
	// クリアカラーを好きなように設定
	glClearColor(0.2f, 0.0f, 0.4f, 0.5f);
	// カラーバッファをクリア
	glClear(GL_COLOR_BUFFER_BIT);

	// @@@
	// シーンを描画

	// バッファを交換、これでシーンが表示される
	SDL_GL_SwapWindow(Game::mWindow);
}

void Renderer::UnloadData()
{
	delete mSpriteVerts;
}

void Renderer::Termination()
{
	SDL_DestroyRenderer(mSdlRenderer);
	SDL_DestroyWindow(Game::mWindow);
}

void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// ソート済みの配列で挿入点を見つける
	// (DrawOrderが小さい順番に描画するため)
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

	// イテレータ―の位置の前に要素を挿入する
	mSprites.insert(iter, _spriteComponent);
}

void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = find(mSprites.begin(), mSprites.end(), _spriteComponent);
	mSprites.erase(iter);
}
