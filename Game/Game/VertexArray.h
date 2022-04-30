#pragma once

/*
頂点バッファとインデックスバッファの作成を行うクラス
*/
class VertexArray
{
public:
	// 頂点レイアウト
	enum class Layout :unsigned char
	{
		//位置&法線&テクスチャUV を持ったフォーマット
		ePosNormTex,
		//位置&法線&"スキン用の影響ボーン＆重み情報" & テクスチャUV 
		ePosNormSkinTex
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_verts">頂点バッファの配列のポインタ</param>
	/// <param name="_numVerts">頂点数</param>
	/// <param name="_indices">インデックスバッファの配列のポインタ</param>
	/// <param name="_numIndices">インデックスの数</param>
	VertexArray(const float* _verts, unsigned int _numVerts,
		const unsigned int* _indices, unsigned int _numIndices);
	// デストラクタ
	~VertexArray();

	// 頂点配列をアクティブにする（描画出来るようにする）
	void SetActive();

private:
	// 頂点バッファにある頂点の数
	unsigned int mNumVerts;
	// インデックスバッファにあるインデックスの数
	unsigned int mNumIndices;
	// 頂点バッファのOpenGL ID
	unsigned int mVertexBuffer;
	// インデックスバッファのOpenGL ID
	unsigned int mIndexBuffer;
	// 頂点配列オブジェクトのOpenGL ID
	unsigned int mVertexArray;

public:  // ゲッター、セッター
	// インデックスバッファにあるインデックスの数を取得する
	unsigned int GetNumIndices() const { return mNumIndices; }
	// 頂点バッファにある頂点の数を取得する
	unsigned int GetNumVerts() const { return mNumVerts; }
};

