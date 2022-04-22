#pragma once

/*
画像の読み込みを行うクラス
*/
class Texture
{
public:
	// コンストラクタ
	Texture();
	// デストラクタ
	~Texture() {};

	/// <summary>
	/// テクスチャのロード
	/// </summary>
	/// <param name="_fileName">テクスチャのファイル名</param>
	/// <returns>true : 成功 , false : 失敗</returns>
	bool Load(const string& _fileName);

private:
	// Surfaceから変換されたテクスチャ
	SDL_Texture* mTex;

	// テクスチャの横幅
	int mWidth;
	// テクスチャの縦幅
	int mHeight;

	// ゲッター、セッター
public:
	// @@@
	// Surfaceから変換されたテクスチャを取得
	SDL_Texture* GetTexture() const { return mTex; }

	// テクスチャの横幅を取得
	int GetWidth() const { return mWidth; }
	// テクスチャの縦幅を取得
	int GetHeight() const { return mHeight; }
};

