#pragma once

// 前方宣言
class Renderer;

/*
メッシュデータを取り扱うクラス
*/
class Mesh
{
public:
	// コンストラクタ
	Mesh();
	// デストラクタ
	~Mesh() {};

	/// <summary>
	/// メッシュデータの読み込み
	/// </summary>
	/// <param name="_fileName">ロードしたいメッシュのファイル名</param>
	/// <param name="_renderer">Rendererクラスのポインタ</param>
	/// <returns>true : 成功 , false : 失敗</returns>
	bool Load(const string& _fileName, Renderer* _renderer);

	// ロードしたメッシュデータの解放
	void Unload();

private:
	// メッシュのテクスチャ群
	vector<Texture*> mTextures;
	// メッシュの頂点配列
	VertexArray* mVertexArray;

	// シェーダーの名前
	string mShaderName;

	// オブジェクト空間での境界球の半径を記録
	float mRadius;

	// 鏡面反射成分の大きさ
	float mSpecPower;
	//// 自己発光強度(HDR)
	//float mLuminance;
	//// 透明度
	//float mAlpha;

public:  // ゲッター、セッター
	// このメッシュに割り当てられた頂点配列を取得
	VertexArray* GetVertexArray() { return mVertexArray; }
	
	// インデックスからテクスチャを取得
	Texture* GetTexture(size_t _index);

	// シェーダ名を取得
	const string& GetShaderName()const { return mShaderName; }

	// オブジェクト空間での境界球の半径を取得
	float GetRadius()const { return mRadius; }
};

