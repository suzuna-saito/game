#pragma once

/*
�t���[���ɂ����������Ԃ��v���������݂���N���X
*/
class FPS
{
public:
	// �R���X�g���N�^
	FPS();
	// �f�X�g���N�^
	~FPS() {};

	// �t���[�����̏���
	void Update();

private:
	// FPS���ݒ�l���傫���Ȃ�Ȃ��悤�ɐ���
	void Wait();

	// �t���[�����[�g�̍ō��l
	const Uint32 MSetFps;
	// 1�t���[���ɂ����鎞��
	const Uint32 MOneFrameTickCount;
	// �t���[���̃J�E���^�[
	Uint32 mFpsCount;
	// FPS�̌v�Z���n�߂����̎���
	Uint32 mFrameStartTickTime;
	// �v�Z�����t���[�����[�g
	Uint32 mFps;
	// �O�̃t���[���̂�����������
	int mBeforeTickCount;
	// ���݂̃t���[���̂�����������
	float mDeltaTime;

	// �Q�b�^�[�A�Z�b�^�[
public:
	// ���݂̃t���[���ɂ����������ԁifloat�^�j
	float GetDeltaTime() { return mDeltaTime; }
};

