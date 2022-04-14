#pragma once

#define TEXTURE Texture::mTexture

/*
画像の読み込みを行うクラス(シングルトン)
*/
class Texture
{
public:
	// インスタンスを作成する
	static void CreateInstance();
	// インスタンスを削除する
	static void DeleteInstance();


	/// <summary>
	/// テクスチャのロード
	/// </summary>
	/// <param name="_fileName">テクスチャのファイル名</param>
	/// <returns>true : 成功 , false : 失敗</returns>
	bool Load(const string& _fileName);

	// 自身のインスタンス
	static Texture* mTexture;

private:
	// コンストラクタ、デストラクタの隠蔽
	Texture();
	~Texture() {};

	// Surfaceから変換されたテクスチャ
	SDL_Texture* mTex;

	// テクスチャの横幅
	int mWidth;
	// テクスチャの縦幅
	int mHeight;

	// ゲッター、セッター
public:
	// Surfaceから変換されたテクスチャを取得
	SDL_Texture* GetTexture() const { return mTex; }

	// テクスチャの横幅を取得
	int GetWidth() const { return mWidth; }
	// テクスチャの縦幅を取得
	int GetHeight() const { return mHeight; }
};

