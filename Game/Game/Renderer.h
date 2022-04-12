#pragma once

#define RENDERER Renderer::mRenderer

/*
�`��i�s���s���N���X(�V���O���g��)
*/
class Renderer
{
public:

	// �C���X�^���X���쐬����
	static void CreateInstance();
	// �C���X�^���X���폜����
	static void DeleteInstance();

	// ����������
	// return true : �����Afalse : ���s
	bool Initialize();

	// �`�揈��
	void Draw();

	// ���[�h�����f�[�^�̉��
	void UnloadData();

	// �I������
	void Termination();

	//���g�̃C���X�^���X
	static Renderer* mRenderer;

private:
	// �R���X�g���N�^�A�f�X�g���N�^�̉B��
	Renderer();
	~Renderer() {};

	// �����_���[�̏�Ԃ��܂ލ\����
	SDL_Renderer* mSdlRenderer;

	// @@@@
	// �X�v���C�g

	//�Q�b�^�[�Z�b�^�[
public:
};

