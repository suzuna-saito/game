#pragma once

/*
フレームにかかった時間を計測し上限を設けるクラス
*/
class FPS
{
public:
	// コンストラクタ
	FPS();
	// デストラクタ
	~FPS() {};

	// フレーム毎の処理
	void Update();

private:
	// FPSが設定値より大きくならないように制御
	void Wait();

	// フレームレートの最高値
	const Uint32 MSetFps;
	// 1フレームにかける時間
	const Uint32 MOneFrameTickCount;
	// フレームのカウンター
	Uint32 mFpsCount;
	// FPSの計算を始めた時の時間
	Uint32 mFrameStartTickTime;
	// 計算したフレームレート
	Uint32 mFps;
	// 前のフレームのかかった時間
	int mBeforeTickCount;
	// 現在のフレームのかかった時間
	float mDeltaTime;

	// ゲッター、セッター
public:
	// 現在のフレームにかかった時間（float型）
	float GetDeltaTime() { return mDeltaTime; }
};

