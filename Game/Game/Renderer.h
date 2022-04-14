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

	// �e�N�X�`����ۊǂ��Ă���A�z�z��
	unordered_map<string, SDL_Texture*>mTextures;

	// @@@@
	// �X�v���C�g

	//�Q�b�^�[�Z�b�^�[
public:
	// �����_���[�̏�Ԃ��܂ލ\���̂̎擾
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	// �g�p�������e�N�X�`�����擾
	SDL_Texture* GetTexture(const string& _fileName);
};

