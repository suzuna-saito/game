#include "pch.h"

Mesh::Mesh()
	: mVertexArray(nullptr)
	, mRadius(0.0f)
	, mSpecPower(100.0f)
	//, mLuminance(1.0f)
	//, mAlpha(1.0f)
{
}

bool Mesh::Load(const string& _fileName, Renderer* _renderer)
{
	// ファイルの読み込み
	ifstream file(_fileName);
	if (!file.is_open())
	{
		SDL_Log("ファイルが見つかりませんでした : Mesh %s", _fileName.c_str());
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
		SDL_Log("Mesh %s は非有効なjsonです", _fileName.c_str());
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
		SDL_Log("Mesh %s にテクスチャがありません", _fileName.c_str());
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
		if (textures.Size() == 1)
		{
			
		}
	}

	if(IsExistMember())

	return true;
}

void Mesh::Unload()
{
}

Texture* Mesh::GetTexture(size_t _index)
{
	return nullptr;
}
