#include "pch.h"

// ���g�̃C���X�^���X�̏�����
Camera* Camera::mCamera = nullptr;

Camera::Camera()
	: Actor(SceneBase::Scene::eInit, Tag::eCamera)
	, mViewpoint(Vector3::Zero)
{
	// �΂ߏォ�猩���낷�ʒu
	mPos = Vector3(0.0f, -1000.0f, 1000.0f);
	mPrevious = mPos;
}

void Camera::CreateInstance()
{
	if (mCamera == nullptr)
	{
		// �C���X�^���X�𐶐�
		mCamera = new Camera();
	}
}

void Camera::DeleteInstance()
{
	if (mCamera != nullptr)
	{
		// �폜
		delete mCamera;
		mCamera = nullptr;
	}
}

void Camera::UpdateActor(float _deltaTime)
{
	// �J�����ʒu���ς���Ă�����X�V����
	if (mCamera->mPrevious != mCamera->mPos)
	{
		// �r���[�s����쐬
		mView = Matrix4::CreateLookAt(mPos, mCamera->mViewpoint, Vector3::UnitZ);
		SetPosition(mPos);
	}
}
