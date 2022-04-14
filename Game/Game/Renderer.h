#pragma once

#define RENDERER Renderer::mRenderer

/*
描画進行を行うクラス(シングルトン)
*/
class Renderer
{
public:

	// インスタンスを作成する
	static void CreateInstance();
	// インスタンスを削除する
	static void DeleteInstance();

	// 初期化処理
	// return true : 成功、false : 失敗
	bool Initialize();

	// 描画処理
	void Draw();

	// ロードしたデータの解放
	void UnloadData();

	// 終了処理
	void Termination();

	//自身のインスタンス
	static Renderer* mRenderer;

private:
	// コンストラクタ、デストラクタの隠蔽
	Renderer();
	~Renderer() {};

	// レンダラーの状態を含む構造体
	SDL_Renderer* mSdlRenderer;

	// テクスチャを保管している連想配列
	unordered_map<string, SDL_Texture*>mTextures;

	// @@@@
	// スプライト

	//ゲッターセッター
public:
	// レンダラーの状態を含む構造体の取得
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	// 使用したいテクスチャを取得
	SDL_Texture* GetTexture(const string& _fileName);
};

