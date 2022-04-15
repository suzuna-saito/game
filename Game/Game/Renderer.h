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

	// �X�v���C�g�̒ǉ�
	void AddSprite(SpriteComponent* _spriteComponent);
	// �X�v���C�g�̍폜
	void RemoveSprite(SpriteComponent* _spriteComponent);

	//���g�̃C���X�^���X
	static Renderer* mRenderer;

private:
	// �R���X�g���N�^�A�f�X�g���N�^�̉B��
	Renderer();
	~Renderer() {};

	// @@@ �g��Ȃ������������
	// Sprite(2D�p)�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	void CreateSpriteVerts();

	// �����_���[�̏�Ԃ��܂ލ\����
	SDL_Renderer* mSdlRenderer;

	// �X�v���C�g�R���|�[�l���g�̔z��
	vector<SpriteComponent*>mSprites;
	// �e�N�X�`����ۊǂ��Ă���A�z�z��
	unordered_map<string, SDL_Texture*>mTextures;

	// @@@
	// �X�v���C�g�p���_
	VertexArray* mSpriteVerts;

	//�Q�b�^�[�Z�b�^�[
public:
	// �����_���[�̏�Ԃ��܂ލ\���̂̎擾
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	// �g�p�������e�N�X�`�����擾
	SDL_Texture* GetTexture(const string& _fileName);
};

