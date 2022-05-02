#include "pch.h"

// 自身のインスタンスの初期化
Camera* Camera::mCamera = nullptr;

Camera::Camera()
	: Actor(SceneBase::Scene::eInit, Tag::eCamera)
	, mViewpoint(Vector3::Zero)
{
	// 斜め上から見下ろす位置
	mPos = Vector3(0.0f, -1000.0f, 1000.0f);
	mPrevious = mPos;
}

void Camera::CreateInstance()
{
	if (mCamera == nullptr)
	{
		// インスタンスを生成
		mCamera = new Camera();
	}
}

void Camera::DeleteInstance()
{
	if (mCamera != nullptr)
	{
		// 削除
		delete mCamera;
		mCamera = nullptr;
	}
}

void Camera::UpdateActor(float _deltaTime)
{
	// カメラ位置が変わっていたら更新する
	if (mCamera->mPrevious != mCamera->mPos)
	{
		// ビュー行列を作成
		mView = Matrix4::CreateLookAt(mPos, mCamera->mViewpoint, Vector3::UnitZ);
		SetPosition(mPos);
	}
}
