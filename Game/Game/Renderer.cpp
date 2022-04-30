#include "pch.h"

// レンダラー実体へのポインタ定義
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
	mRenderer->mSdlRenderer = SDL_CreateRenderer(Game::mWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer->mSdlRenderer)
	{
		printf("SDLRendererの作成に失敗 : %s", SDL_GetError());
		return false;
	}

	// シェーダーのロード
	if (!mRenderer->LoadShaders())
	{
		SDL_Log("シェーダーのロードに失敗しました");
		return false;
	}

	// スプライト用の頂点配列を作成
	mRenderer->CreateSpriteVerts();

	return true;
}

void Renderer::Draw()
{
	//@@@(設定しなかったら黒になる)
	// クリアカラーを好きなように設定
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
	// カラーバッファをクリア
	glClear(GL_COLOR_BUFFER_BIT);

	// mSpritesの中にデータがあれば
	if (mRenderer->mSprites.size() != 0)
	{
		// スプライトの描画
		mRenderer->SpriteDraw();
	}

	// バッファを交換、これでシーンが表示される
	SDL_GL_SwapWindow(Game::mWindow);
}

void Renderer::SpriteDraw()
{
	// Spriteの描画。αブレンドを有効にする
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,             // srcFactorはsrcAlpha
		GL_ONE_MINUS_SRC_ALPHA);  // dstFactorは(1-srcAlpha)

	// スプライトシェーダーをアクティブにする
	// スプライト頂点配列を有効にする
	mRenderer->mSpriteShader->SetActive();
	mRenderer->mSpriteVerts->SetActive();
	// 全てのスプライトの描画
	for (auto sprite : mRenderer->mSprites)
	{
		sprite->Draw(mRenderer->mSpriteShader);
	}
}

bool Renderer::LoadShaders()
{
	// スプライトシェーダーの生成
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// ビュー射影行列を作成し、設定
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(Game::MWidth, Game::MHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	return true;
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

void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = find(mRenderer->mSprites.begin(), mRenderer->mSprites.end(), _spriteComponent);
	mRenderer->mSprites.erase(iter);
}

Texture* Renderer::GetTexture(const string& _fileName)
{
	Texture* texture = nullptr;

	// すでに作成されていないか調べる
	auto itr = mTextures.find(_fileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	// 作成済みでない場合、新しくテクスチャを作成
	else
	{
		texture = new Texture();
		if (texture->Load(_fileName))
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

Mesh* Renderer::GetMesh(const string& _fileName)
{
	return nullptr;
}

void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// ソート済みの配列で挿入点を見つける
	// (DrawOrderが小さい順番に描画するため)
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

	// イテレータ―の位置の前に要素を挿入する
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