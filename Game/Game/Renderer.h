#pragma once

/*
�`��i�s���s���N���X
*/
class Renderer
{
public:
	// �R���X�g���N�^
	Renderer();
	// �f�X�g���N�^
	~Renderer() {};

	// �C���X�^���X���쐬����
	static void CreateInstance();
	// �C���X�^���X���폜����
	static void DeleteInstance();

	// ����������
	// return true : �����Afalse : ���s
	static bool Initialize();

	// �`�揈��
	static void Draw();

	// ���[�h�����f�[�^�̉��
	static void UnloadData();

	// �I������
	static void Termination();

	// �V�F�[�_�[�̓ǂݍ���
	static bool LoadShaders();

	// @@@ �g��Ȃ������������
	// Sprite(2D�p)�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	static void CreateSpriteVerts();

	// �X�v���C�g�̒ǉ�
	static void AddSprite(SpriteComponent* _spriteComponent);
	// �X�v���C�g�̍폜
	static void RemoveSprite(SpriteComponent* _spriteComponent);

private:
	// ���g�̃C���X�^���X
	static Renderer* mRenderer;

	// �X�v���C�g�R���|�[�l���g�̔z��
	vector<SpriteComponent*>mSprites;

	// @@@
	// �e�N�X�`����ۊǂ��Ă���A�z�z�� gluint�^?
	unordered_map<string, SDL_Texture*>mTextures;

	// @@@
	/* �N���X�̃|�C���^ */
	// �X�v���C�g
	Shader* mSpriteShader;
	// �X�v���C�g�p���_
	VertexArray* mSpriteVerts;

	//�Q�b�^�[�Z�b�^�[
public:
	// �����_���[�̏�Ԃ��܂ލ\���̂̎擾
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	// @@@ gl�ɂȂ�ƌ^�Ⴄ�H
	// �g�p�������e�N�X�`�����擾 
	SDL_Texture* GetTexture(const string& _fileName);
};

