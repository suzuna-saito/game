#include "pch.h"

// レンダラー実体へのポインタ定義
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
		printf("シェーダーのロードに失敗しました\n");
		return false;
	}

	// スプライト用の頂点配列を作成
	mRenderer->CreateSpriteVerts();

	return true;
}

void Renderer::Draw()
{
	//@@(設定しなかったら黒になる)
	// クリアカラーを好きなように設定
	/*glClearColor(1.0f, 1.0f, 1.0f, 0.5f);*/
	// カラーバッファをクリア
	glClear(GL_COLOR_BUFFER_BIT);

	// Spriteの描画。αブレンドを有効にする
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,             // srcFactorはsrcAlpha
		GL_ONE_MINUS_SRC_ALPHA);  // dstFactorは(1-srcAlpha)

	// mSpritesの中にデータがあれば
	if (mRenderer->mSprites.size() != 0)
	{
		// スプライトの描画
		mRenderer->SpriteDraw();
	}

	// デプスバッファ法有効 / αブレンディング無効
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	// メッシュコンポーネントの描画
	// 基本的なメッシュシェーダーをアクティブにする
	mRenderer->mMeshShader->SetActive();
	// ビュー射影行列を更新する
	mRenderer->mMeshShader->SetMatrixUniform("uViewProj", mRenderer->mView * mRenderer->mProjection);
	// @@@ シェーダーに渡すライティング情報を更新する
	// 全てのメッシュの描画
	for (auto mc : mRenderer->mMeshComponents)
	{
		mc->Draw(mRenderer->mMeshShader);
	}

	// バッファを交換、これでシーンが表示される
	SDL_GL_SwapWindow(Game::mWindow);
}

void Renderer::SpriteDraw()
{
	// スプライトシェーダーをアクティブにする
	// スプライト頂点配列を有効にする
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	// 全てのスプライトの描画
	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
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

	// @@@ 後で読み取るファイル変えといて
	// 標準メッシュシェーダーの作成
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

void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = find(mRenderer->mSprites.begin(), mRenderer->mSprites.end(), _spriteComponent);
	mRenderer->mSprites.erase(iter);
}

void Renderer::AddMeshComponent(MeshComponent* _meshComponent)
{
	// スケルトンデータを用いる場合
	if (_meshComponent->GetIsSkeltal())
	{
		// スケルタルメッシュコンポーネント
	}
	else
	{
		mRenderer->mMeshComponents.emplace_back(_meshComponent);
	}
}

void Renderer::RemoveMeshcomponent(MeshComponent* _meshComponent)
{
	// スケルトンデータを用いる場合
	if (_meshComponent->GetIsSkeltal())
	{
		// スケルタルメッシュコンポーネント
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

	// すでに作成されていないか調べる
	auto itr = mRenderer->mTextures.find(_fileName);
	if (itr != mRenderer->mTextures.end())
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
			mRenderer->mTextures.emplace(_fileName, texture);
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
	Mesh* m = nullptr;

	// すでに作成されていないか調べる
	auto itr = mRenderer->mMeshes.find(_fileName);
	if (itr != mRenderer->mMeshes.end())
	{
		m = itr->second;
	}
	// 作成済みでない場合、新しくメッシュを作成
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