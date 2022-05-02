#pragma once

/*
描画進行を行うクラス
*/
class Renderer
{
public:
	// コンストラクタ
	Renderer();
	//デストラクタ
	~Renderer() {};

	// インスタンスを作成する
	static void CreateInstance();
	// インスタンスを削除する
	static void DeleteInstance();

	// 初期化処理
	// return true : 成功、false : 失敗
	static bool Initialize();

	// 描画処理
	static void Draw();

	// ロードしたデータの解放
	static void UnloadData();

	// 終了処理
	static void Termination();

	// スプライトの追加
	static void AddSprite(SpriteComponent* _spriteComponent);
	// スプライトの削除
	static void RemoveSprite(SpriteComponent* _spriteComponent);

	// メッシュコンポーネントの追加
	static void AddMeshComponent(MeshComponent* _meshComponent);
	// メッシュコンポーネントの削除
	static void RemoveMeshcomponent(MeshComponent* _meshComponent);

	// レンダラーの実体（アプリ内に唯一存在）
	static Renderer* mRenderer;

private:
	// シェーダーの読み込み
	bool LoadShaders();

	// @@@ 使わなかったら消して
	// Sprite(2D用)の頂点バッファとインデックスバッファの作成
	void CreateSpriteVerts();
	// スプライトの描画処理
	void SpriteDraw();

	// レンダラーの状態を含む構造体
	SDL_Renderer* mSdlRenderer;

	// スプライトコンポーネントの配列
	vector<SpriteComponent*>mSprites;
	// メッシュコンポーネントの配列
	vector<MeshComponent*>mMeshComponents;
	// テクスチャを保管している連想配列
	unordered_map<string, Texture*>mTextures;

	/* クラスのポインタ */
	// スプライト
	Shader* mSpriteShader;
	// スプライト用頂点
	VertexArray* mSpriteVerts;

public:  //ゲッターセッター
	// 使用したいテクスチャを取得
	static Texture* GetTexture(const string& _fileName);

	// 使用したいメッシュを取得
	Mesh* GetMesh(const string& _fileName);
};