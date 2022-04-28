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

	// ロードしたテクスチャの解放
	void Unload();

private:
	// このテクスチャのOpenGL ID
	unsigned int mTextureID;
	
	// テクスチャの横幅
	int mWidth;
	// テクスチャの縦幅
	int mHeight;

public:  // ゲッター、セッター
	// テクスチャIDを取得
	int GetTextureID()const { return mTextureID; }
	// テクスチャの横幅を取得
	int GetWidth() const { return mWidth; }
	// テクスチャの縦幅を取得
	int GetHeight() const { return mHeight; }
};

