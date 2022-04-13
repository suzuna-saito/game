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
};

