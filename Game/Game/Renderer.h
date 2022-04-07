#pragma once

#define RENDERER Renderer::GetInstance();

/*
描画進行を行うクラス
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
	// 終了処理
	void Termination();

	// 描画処理
	void Draw();

private:
	//自身のインスタンス
	static Renderer* mRenderer;

	//ゲッターセッター
public:
	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns>Rendererクラスのインスタンス</returns>
	static Renderer* GetInstance() { return mRenderer; }

};

