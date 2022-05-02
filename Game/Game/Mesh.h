#pragma once

// 前方宣言
class Renderer;

/*
メッシュデータを取り扱うクラス
*/
class Mesh
{
public:
	union Vertex
	{
		float f;
		uint8_t b[4];
	};

	// テクスチャタイプ
	enum class TextureType :unsigned char
	{
		// ディフューズ(ベースカラー)
		eDiffuseMap,
		// ノーマル(法線)
		eNormalMap,
		// スペキュラ(反射光)
		eSpecularMap,
		// エミッシプ(放射光)
		eEmissiveMap,
	};

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
	/// <summary>
	/// テクスチャを読み込んで、タイプ別に保存
	/// </summary>
	/// <param name="_doc">解析オブジェクト</param>
	void Classification(const rapidjson::Document& _doc);
	/// <summary>
	/// テクスチャタイプを読み込み
	/// </summary>
	/// <param name="_doc">解析オブジェクト</param>
	/// <param name="_texType">テクスチャタイプ</param>
	/// <param name="_typeString">メンバ名</param>
	/// <returns>テクスチャのID（int型）</returns>
	int LoadTypeTexture(const rapidjson::Document& _doc, TextureType _texType, const char* _typeString);

	// 頂点レイアウトがPosNormTexだった場合の処理
	void IfPosNormTex(const rapidjson::Value& _vert, vector<Vertex>& _vertices);
	// 頂点レイアウトがPosNormSkinTexだった場合の処理
	void IfPosNormSkinTex(const rapidjson::Value& _vert, vector<Vertex>& _vertices);

	// テクスチャタイプに割り当てられたテクスチャ
	unordered_map<TextureType, int> mTexturesByType;

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

