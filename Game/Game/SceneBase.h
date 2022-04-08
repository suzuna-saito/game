#pragma once

/*
各シーンの基底クラス
*/
class SceneBase
{
public:
	// コンストラクタ
	SceneBase();
	// デストラクタ
	~SceneBase() {};

	// 毎フレームの入力処理
	virtual void Input(const InputState& _state) = 0;

	// 毎フレームの更新処理
	virtual SceneBase* Update() = 0;

	// シーンのタグ（種類）
	enum class Scene :unsigned char
	{
		// 初期化
		eInit,
		// タイトル
		eTitle,
		// @@@ end
		eEnd,
	};

	// 現在のシーンタグ
	static Scene mIsScene;

protected:
	// 次のシーンに遷移するか
	// true : する false : しない
	bool mSceneTransitionFlag;

};

