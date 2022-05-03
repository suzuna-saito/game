#pragma once

/*
�J����(�Œ�)
*/
class Camera :public Actor
{
public:
	// �R���X�g���N�^
	Camera();
	// �f�X�g���N�^
	~Camera() {};

	// �C���X�^���X���쐬����
	static void CreateInstance();
	// �C���X�^���X���폜����
	static void DeleteInstance();

	// �J�����̃A�b�v�f�[�g
	void UpdateActor(float _deltaTime)override;

private:
	// Camera�̎��́i�A�v�����ɗB�ꑶ�݁j
	static Camera* mCamera;
	
	// �����_
	Vector3 mViewpoint;

	// �J�����ʒu��ۑ�����
	Vector3 mPrevious;
};