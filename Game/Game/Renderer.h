#pragma once

/*
描画進行を行うクラス
*/
class Renderer
{
public:
	// コンストラクタ
	Renderer();
	// デストラクタ
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

	// シェーダーの読み込み
	static bool LoadShaders();

	// @@@ 使わなかったら消して
	// Sprite(2D用)の頂点バッファとインデックスバッファの作成
	static void CreateSpriteVerts();

	// スプライトの追加
	static void AddSprite(SpriteComponent* _spriteComponent);
	// スプライトの削除
	static void RemoveSprite(SpriteComponent* _spriteComponent);

private:
	// 自身のインスタンス
	static Renderer* mRenderer;

	// スプライトコンポーネントの配列
	vector<SpriteComponent*>mSprites;

	// @@@
	// テクスチャを保管している連想配列 gluint型?
	unordered_map<string, SDL_Texture*>mTextures;

	// @@@
	/* クラスのポインタ */
	// スプライト
	Shader* mSpriteShader;
	// スプライト用頂点
	VertexArray* mSpriteVerts;

	//ゲッターセッター
public:
	// レンダラーの状態を含む構造体の取得
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	// @@@ glになると型違う？
	// 使用したいテクスチャを取得 
	SDL_Texture* GetTexture(const string& _fileName);
};

