#pragma once

// @@ 2Dの描画だからこのクラス使わない可能性あり。その場合消して
// って、なったらテクスチャクラスをシングルトンにする必要ないかも？

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

	// 描画処理
	virtual void Draw(Shader* _shader);

protected:
	// 描画される順番
	int mDrawOrder;
	// テクスチャの横幅
	int mTexWidth;
	// テクスチャの縦幅
	int mTexHeight;

	// ゲッター、セッター
public:
	// 描画される順番を取得
	int GetDrawOrder() const { return mDrawOrder; }

	//// @ メモ　レンダラーの中のテクスチャを作成した所で呼ぶ
	//// テクスチャの横幅、縦幅をセット
	//int SetTexSize(int _w, int _h) { mTexWidth = _w; mTexHeight = _h; }
};

