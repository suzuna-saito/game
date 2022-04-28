#pragma once

/*
タイトルシーンのクラス
*/
class Title :public SceneBase
{
public:
	// コンストラクタ
	Title(const Scene& _nowScene);
	// デストラクタ
	~Title();

	// 毎フレームの入力処理
	void Input(const InputState& _state) override;

	// 毎フレームの更新処理
	SceneBase* Update() override;
};

