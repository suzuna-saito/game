#pragma once

/*
カメラ(固定)
*/
class Camera :public Actor
{
public:
	// コンストラクタ
	Camera();
	// デストラクタ
	~Camera() {};

	// インスタンスを作成する
	static void CreateInstance();
	// インスタンスを削除する
	static void DeleteInstance();

	// カメラのアップデート
	void UpdateActor(float _deltaTime)override;

private:
	// Cameraの実体（アプリ内に唯一存在）
	static Camera* mCamera;
	
	// 注視点
	Vector3 mViewpoint;

	// カメラ位置を保存する
	Vector3 mPrevious;
};