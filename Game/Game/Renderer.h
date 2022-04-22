#pragma once

/*
�`��i�s���s���N���X
*/
class Renderer
{
public:
	// �R���X�g���N�^
	Renderer();
	//�f�X�g���N�^
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

	// �X�v���C�g�̒ǉ�
	static void AddSprite(SpriteComponent* _spriteComponent);
	// �X�v���C�g�̍폜
	static void RemoveSprite(SpriteComponent* _spriteComponent);

	// �����_���[�̎��́i�A�v�����ɗB�ꑶ�݁j
	static Renderer* mRenderer;

private:
	// �V�F�[�_�[�̓ǂݍ���
	bool LoadShaders();

	// @@@ �g��Ȃ������������
	// Sprite(2D�p)�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	void CreateSpriteVerts();

	// �����_���[�̏�Ԃ��܂ލ\����
	SDL_Renderer* mSdlRenderer;

	// �X�v���C�g�R���|�[�l���g�̔z��
	vector<SpriteComponent*>mSprites;
	// �e�N�X�`����ۊǂ��Ă���A�z�z�� gluint�^
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
	static SDL_Renderer* GetSDLRenderer() { return mRenderer->mSdlRenderer; }

	// �g�p�������e�N�X�`�����擾
	SDL_Texture* GetTexture(const string& _fileName);
};

