#include "pch.h"

//-------------------------------------------------------------------------------------------------------------------+
// 頂点レイアウト
// PosNormTex = 8 * sizeof(float) = 32 bytes
// | 位置      | 法線      | Texture|
// | x | y | z | x | y | z | u | v | 
//
// posNormSkinTex
// PosNormSkinTex = (8 * sizeof(float)) + (8 * sizeof(char)) = 40 bytes
// | 位置      | 法線       | Bones   | weight  |Texture|
// | x | y | z | x | y | z | char[4] | char[4] | u | v |
//                                    ※weightの確保はcharだが、精度が必要ないので8bit固定小数として使用する
//-------------------------------------------------------------------------------------------------------------------+

VertexArray::VertexArray(const void* _verts, unsigned int _numVerts, const unsigned int* _indices, unsigned int _numIndices,Layout _layout)
	: mNumVerts(_numVerts)
	, mNumIndices(_numIndices)
{
	// 頂点配列を作成
	glGenVertexArrays(1, &mVertexArray);
	// IDをmVertexArrayに保存
	glBindVertexArray(mVertexArray);

	// 頂点レイアウトが スケルタルモデルなら　ボーンID、影響度分をサイズ増やす
	unsigned vertexSize = 8 * sizeof(float);
	if (_layout == Layout::ePosNormSkinTex)
	{
		vertexSize = 8 * sizeof(float) + 8 * sizeof(char);
	}

	// 頂点バッファの作成
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	// _vertsを頂点バッファにコピーする
	glBufferData(
		GL_ARRAY_BUFFER,						// バッファの種類
		_numVerts * vertexSize * sizeof(float),	// コピーするバイト数
		_verts,									// コピー元（ポインタ）
		GL_STATIC_DRAW							// このデータの利用方法
	);

	// インデックスバッファの作成
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	// _indicesをインデックスバッファにコピーする
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			// インデックスバッファの指定
		_numIndices * sizeof(unsigned int),	// データのサイズ
		_indices, GL_STATIC_DRAW
	);

	// レイアウトがPosNormTexだった場合
	if (_layout == Layout::ePosNormTex)
	{
		IfPosNormTex(vertexSize);
	}
	else
	{
		IfPosNormSkinTex(vertexSize);
	}
	
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	// 利用する頂点配列を指定する
	glBindVertexArray(mVertexArray);
}

void VertexArray::IfPosNormTex(unsigned _vertexSize)
{
	// 最初の頂点属性を有効にする(位置座標)
	glEnableVertexAttribArray(0);
	// 属性のサイズ、種類、フォーマットを指定
	glVertexAttribPointer(
		0,								// 頂点属性インデックス（位置座標）
		3,								// 要素の数
		GL_FLOAT,						// 要素の型
		GL_FALSE,						// （GL_FLOATには使わない）
		sizeof(float) * _vertexSize,	// 各頂点のサイズ
		0								// 頂点データの開始位置からこの属性までのオフセット
	);

	//第2の頂点属性を有効に（法線ベクトル）
	glEnableVertexAttribArray(1);
	// 属性のサイズ、種類、フォーマットを指定
	glVertexAttribPointer(
		1,								// 頂点属性インデックス（法線ベクトル）
		3,								// 要素の数
		GL_FLOAT,						// 要素の型
		GL_FALSE,						// （GL_FLOATには使わない）
		sizeof(float) * _vertexSize,	// 各頂点のサイズ
		reinterpret_cast<void*>(sizeof(float) * 3)	//オフセットポインタ
	);

	//第3の頂点属性を有効に（テクスチャ座標）
	glEnableVertexAttribArray(2);
	// 属性のサイズ、種類、フォーマットを指定
	glVertexAttribPointer(
		2,								// 頂点属性インデックス（テクスチャ座標）
		2,								// 要素の数（UVは2個）
		GL_FLOAT,						// 要素の型
		GL_FALSE,						// （GL_FLOATには使わない）
		sizeof(float) * _vertexSize,	// 各頂点のサイズ
		reinterpret_cast<void*>(sizeof(float) * 6)	//オフセットポインタ
	);
}

void VertexArray::IfPosNormSkinTex(unsigned _vertexSize)
{
	// float 3個分　→　位置 x,y,z　位置属性をセット
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vertexSize, 0);
	// 次のfloat 3個分 → 法線 nx, ny, nz　法線属性をセット
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _vertexSize,
		reinterpret_cast<void*>(sizeof(float) * 3));
	//　影響受けるボーンインデックス番号  (int型をキープ)
	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, _vertexSize,
		reinterpret_cast<void*>(sizeof(float) * 6));
	// ボーンウェイト情報 (float に変換)
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, _vertexSize,
		reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
	// 次のfloat 2個分 u, v  テクスチャ座標属性をセット
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, _vertexSize,
		reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
}
