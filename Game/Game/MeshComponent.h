#pragma once

// 前方宣言
class Mesh;

/*
メッシュデータの管理と描画を行なう
*/
class MeshComponent :public Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするアクターのポインター</param>
	/// <param name="_skelton">スケルトンデータを用いるか</param>
	MeshComponent(Actor* _owner, bool _skelton = false);

	// デストラクタ
	~MeshComponent();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_shader">使用するシェーダー</param>
	virtual void Draw(Shader* _shader);

protected:
	/// <summary>
	/// テクスチャタイプごとにセット
	/// </summary>
	/// <param name="_shader">使用するシェーダークラス</param>
	void SetTextureToShader(Shader* _shader);

	// メッシュデータ
	Mesh* mMesh;

	// スケルトンデータを用いるか
	bool mSkeltonFlag;

public:  // ゲッター、セッター
	// スケルトンデータを用いるかのフラグを取得
	bool GetIsSkeltal()const { return mSkeltonFlag; }

	// メッシュコンポーネントが使うmMeshの設定
	virtual void SetMesh(Mesh* _mesh) { mMesh = _mesh; }
};

