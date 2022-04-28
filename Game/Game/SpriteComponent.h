#pragma once

// @@ 2Dの描画だからこのクラス使わない可能性あり。その場合消して
// って、なったらテクスチャクラスをシングルトンにする必要ないかも？

// 前方宣言
class Texture;

/*
スクリーン上に画像データを描画するクラス
*/
class SpriteComponent :public Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするアクターのポインタ</param>
	/// <param name="_drawOrder">数値が低いほど遠くに描画される</param>
	SpriteComponent(Actor* _owner, int _drawOrder = 100);
	// デストラクタ
	~SpriteComponent();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_shader">使用するシェーダークラスのポインタ</param>
	virtual void Draw(Shader* _shader);

protected:
	// Texture*のメンバー変数
	Texture* mTexture;

	// 描画される順番
	int mDrawOrder;
	// テクスチャの横幅
	int mTexWidth;
	// テクスチャの縦幅
	int mTexHeight;

public:  // ゲッター、セッター
	// 描画される順番を取得
	int GetDrawOrder() const { return mDrawOrder; }

	//// @ メモ　レンダラーの中のテクスチャを作成した所で呼ぶ
	//// テクスチャの横幅、縦幅をセット
	//int SetTexSize(int _w, int _h) { mTexWidth = _w; mTexHeight = _h; }
};

