#include "pch.h"

Mesh::Mesh()
	: mVertexArray(nullptr)
	, mRadius(0.0f)
	, mSpecPower(100.0f)
	//, mLuminance(1.0f)
	//, mAlpha(1.0f)
{
	mTexturesByType.emplace(TextureType::eDiffuseMap, 0);
	mTexturesByType.emplace(TextureType::eNormalMap, 0);
	mTexturesByType.emplace(TextureType::eSpecularMap, 0);
	mTexturesByType.emplace(TextureType::eEmissiveMap, 0);
}

bool Mesh::Load(const string& _fileName, Renderer* _renderer)
{
	// ファイルの読み込み
	ifstream file(_fileName);
	if (!file.is_open())
	{
		printf("ファイルが見つかりませんでした : Mesh %s", _fileName.c_str());
		return false;
	}

	// filestreamにファイル文字列を取り込む
	stringstream fileStream;
	fileStream << file.rdbuf();
	string contents = fileStream.str();
	// ファイル文字列をjson文字列に変換
	rapidjson::StringStream jsonStr(contents.c_str());
	// 解析オブジェクト作成
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	// JSONオブジェクトか？
	if (!doc.IsObject())
	{
		printf("Mesh %s は非有効なjsonです", _fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// バージョンチェック
	if (ver != 1)
	{
		printf("Mesh %s はバージョンが1ではありません", _fileName.c_str());
		return false;
	}

	mShaderName = doc["shader"].GetString();

	// 頂点レイアウトとサイズをファイルからセット
	VertexArray::Layout layout = VertexArray::Layout::ePosNormTex;
	size_t vertSize = 8;

	string vertexFormat = doc["vertexformat"].GetString();
	if (vertexFormat == "PosNormSkinTex")
	{
		layout = VertexArray::Layout::ePosNormSkinTex;
		// これは "Vertex "ユニオンの数です, which is 8 + 2 (for skinning)s　1個の頂点の集合の数　８　＋　２（スキニング分）
		// 3 (位置xyz) + 3(法線xyz) + 2(Boneと重み）＋　2(UV)  の計　10個分（40byte) 　
		vertSize = 10;
	}

	// テクスチャのロード
	const rapidjson::Value& textures = doc["textures"];
	if (!textures.IsArray() || textures.Size() < 1)
	{
		printf("Mesh %s にtexturesがありません", _fileName.c_str());
		return false;
	}

	// スペキュラ強度
	mSpecPower = static_cast<float>(doc["specularPower"].GetDouble());

	//@@@ エミッシプってなんぞ。スペキュラってなんぞ
	//// エミッシプ強度値(定義されていれば)
	//if (IsExistMember(doc, "luminance"))
	//{
	//	mLuminance = ForceGetFloat(doc["luminance"]);
	//}

	//// 透明度
	//if (IsExistMember(doc, "alpha"))
	//{
	//	mAlpha = ForceGetFloat(doc["alpha"]);
	//}

	for (rapidjson::SizeType i = 0; i < textures.Size(); ++i)
	{
		// すでにロードされてテクスチャじゃないか調べる
		string texName = textures[i].GetString();
		Texture* t = _renderer->GetTexture(texName);
		// テクスチャが取得できなかった場合
		if (t == nullptr)
		{
			// デフォルトのテクスチャを使用
			t = _renderer->GetTexture("Assets/Actor/Texture/Default.png");
		}
		// メッシュのテクスチャ群に追加
		mTextures.emplace_back(t);

		// @@@　？？？
		// テクスチャが一つの時はdiffusemapのみ所持してる？
		if (textures.Size() == 1)
		{
			mTexturesByType[TextureType::eDiffuseMap] = t->GetTextureID();
		}
	}

	// タイプ別テクスチャ読み込み
	Classification(doc);

	// 頂点配列データをロード
	const rapidjson::Value& VertsJson = doc["vertices"];
	if (!VertsJson.IsArray() || VertsJson.Size() < 1)
	{
		printf("Mesh %s にverticesがありません", _fileName.c_str());
		return false;
	}

	// 最適にメモリを確保できるよう、あらかじめサイズ変更の予定を指示
	vector<Vertex> vertices;
	vertices.reserve(VertsJson.Size() * vertSize);

	mRadius = 0.0f;
	for (rapidjson::SizeType i = 0; i < VertsJson.Size(); ++i)
	{
		// 今のところは8つの要素とする
		const rapidjson::Value& Vert = VertsJson[i];
		if (!Vert.IsArray())
		{
			printf("予期しない頂点フォーマットです %s", _fileName.c_str());
			return false;
		}
		///////////////////////////////////////////////////////////////////////////////
		Vector3 pos(static_cast<float>(Vert[0].GetDouble()),
			static_cast<float>(Vert[1].GetDouble()),
			static_cast<float>(Vert[2].GetDouble()));

		mRadius = Math::Max(mRadius, pos.LengthSq());

		// 頂点レイアウトがPosNormTexなら（ボーンがない）
		if (layout == VertexArray::Layout::ePosNormTex)
		{
			IfPosNormTex(Vert, vertices);
		}
		else
		{
			IfPosNormSkinTex(Vert, vertices);
		}
	}

	// 半径を2条する
	mRadius = Math::Sqrt(mRadius);

	// 要素配列データのロード
	const rapidjson::Value& IndJson = doc["indices"];
	if (!IndJson.IsArray() || IndJson.Size() < 1)
	{
		printf("Mesh %s にindicesはありません", _fileName.c_str());
		return false;
	}

	vector<unsigned int>indices;
	indices.reserve(IndJson.Size() * 3);

	for (rapidjson::SizeType i = 0; i < IndJson.Size(); ++i)
	{
		const rapidjson::Value& Ind = IndJson[i];
		if (!Ind.IsArray() || Ind.Size() != 3)
		{
			printf("無効なインデックスです %s", _fileName.c_str());
			return false;
		}

		indices.emplace_back(Ind[0].GetUint());
		indices.emplace_back(Ind[1].GetUint());
		indices.emplace_back(Ind[2].GetUint());
	}

	// ここでVertexArrayクラスの作成
	mVertexArray = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
		indices.data(), static_cast<unsigned>(indices.size()), layout);

	return true;
}

void Mesh::Unload()
{
}

void Mesh::Classification(const rapidjson::Document& _doc)
{
	// ディフューズ
	if (IsExistMember(_doc, "diffusemap"))
	{
		mTexturesByType[TextureType::eDiffuseMap]
			= LoadTypeTexture(_doc, TextureType::eDiffuseMap, "diffusemap");
	}
	// ノーマル
	if (IsExistMember(_doc, "normalmap"))
	{
		mTexturesByType[TextureType::eNormalMap]
			= LoadTypeTexture(_doc, TextureType::eNormalMap, "normalmap");
	}
	// スペキュラ
	if (IsExistMember(_doc, "specularmap"))
	{
		mTexturesByType[TextureType::eSpecularMap]
			= LoadTypeTexture(_doc, TextureType::eSpecularMap, "specularmap");
	}
	// エミッシプ
	if (IsExistMember(_doc, "emissivemap"))
	{
		mTexturesByType[TextureType::eEmissiveMap]
			= LoadTypeTexture(_doc, TextureType::eEmissiveMap, "emissivemap");
	}
}

int Mesh::LoadTypeTexture(const rapidjson::Document& _doc, TextureType _texType, const char* _typeString)
{
	string noneTexture("none");
	string texName;
	Texture* t;

	texName = _doc[_typeString].GetString();
	if (texName != noneTexture)
	{
		// 使用したいテクスチャを取得
		t = Renderer::GetTexture(texName);

		// テクスチャが取得できなかった場合
		if (t == nullptr)
		{
			// デフォルトのテクスチャを使用
			t = Renderer::GetTexture("Assets/Actor/Texture/Default.png");
		}

		return t->GetTextureID();
	}

	return 0;
}

void Mesh::IfPosNormTex(const rapidjson::Value& _vert, vector<Vertex>& _vertices)
{
	Vertex v;
	// float値を追加
	for (rapidjson::SizeType j = 0; j < _vert.Size(); ++j)
	{
		v.f = static_cast<float>(_vert[j].GetDouble());
		_vertices.emplace_back(v);
	}
}

void Mesh::IfPosNormSkinTex(const rapidjson::Value& _vert, vector<Vertex>& _vertices)
{
	Vertex v;
	// 頂点と法線を追加 6個分
	for (rapidjson::SizeType j = 0; j < 6; ++j)
	{
		v.f = static_cast<float>(_vert[j].GetDouble());
		_vertices.emplace_back(v);
	}

	// スキン情報追加（ボーン番号：unsigned charの1バイト分）
	// ループとしては2回転する　1回転目はボーン番号、2回転目はボーンウェイトをintとして取ってくる（使用時に不動少数化する？）
	for (rapidjson::SizeType j = 6; j < 14; j += 4)
	{
		v.b[0] = _vert[j].GetUint();
		v.b[1] = _vert[j + 1].GetUint();
		v.b[2] = _vert[j + 2].GetUint();
		v.b[3] = _vert[j + 3].GetUint();
		_vertices.emplace_back(v);
	}

	// テクスチャ座標追加
	for (rapidjson::SizeType j = 14; j < _vert.Size(); ++j)
	{
		v.f = static_cast<float>(_vert[j].GetDouble());
		_vertices.emplace_back(v);
	}
}

//Texture* Mesh::GetTexture(size_t _index)
//{
//	return nullptr;
//}
