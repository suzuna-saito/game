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

VertexArray::VertexArray(const float* _verts, unsigned int _numVerts, const unsigned int* _indices, unsigned int _numIndices)
	: mNumVerts(_numVerts)
	, mNumIndices(_numIndices)
{
	// 頂点配列を作成
	glGenVertexArrays(1, &mVertexArray);
	// IDをmVertexArrayに保存
	glBindVertexArray(mVertexArray);

	// 頂点バッファの作成
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	// _vertsを頂点バッファにコピーする
	glBufferData(
		GL_ARRAY_BUFFER,				// バッファの種類
		_numVerts * 8 * sizeof(float),	// コピーするバイト数
		_verts,							// コピー元（ポインタ）
		GL_STATIC_DRAW					// このデータの利用方法
	);

	// インデックスバッファの作成
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	// _indicesをインデックスバッファにコピーする
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			// インデックスバッファの指定
		_numVerts * sizeof(unsigned int),	// データのサイズ
		_indices, GL_STATIC_DRAW
	);

	// 最初の頂点属性を有効にする(位置座標)
	glEnableVertexAttribArray(0);

	// 属性のサイズ、種類、フォーマットを指定
	glVertexAttribPointer(
		0,					// 頂点属性インデックス（位置座標）
		3,					// 要素の数
		GL_FLOAT,			// 要素の型
		GL_FALSE,			// （GL_FLOATには使わない）
		sizeof(float) * 8,	// 各頂点のサイズ
		0					// 頂点データの開始位置からこの属性までのオフセット
	);

	// @@@
	// 第二、第三の頂点属性を有効に
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
