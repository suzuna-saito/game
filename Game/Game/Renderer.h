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

	// ���b�V���R���|�[�l���g�̒ǉ�
	static void AddMeshComponent(MeshComponent* _meshComponent);
	// ���b�V���R���|�[�l���g�̍폜
	static void RemoveMeshcomponent(MeshComponent* _meshComponent);

	// �����_���[�̎��́i�A�v�����ɗB�ꑶ�݁j
	static Renderer* mRenderer;

private:
	// �V�F�[�_�[�̓ǂݍ���
	bool LoadShaders();

	// @@@ �g��Ȃ������������
	// Sprite(2D�p)�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	void CreateSpriteVerts();
	// �X�v���C�g�̕`�揈��
	void SpriteDraw();

	// �����_���[�̏�Ԃ��܂ލ\����
	SDL_Renderer* mSdlRenderer;

	// �X�v���C�g�R���|�[�l���g�̔z��
	vector<SpriteComponent*>mSprites;
	// ���b�V���R���|�[�l���g�̔z��
	vector<MeshComponent*>mMeshComponents;
	// �e�N�X�`����ۊǂ��Ă���A�z�z��
	unordered_map<string, Texture*>mTextures;

	/* �N���X�̃|�C���^ */
	// �X�v���C�g
	Shader* mSpriteShader;
	// �X�v���C�g�p���_
	VertexArray* mSpriteVerts;

public:  //�Q�b�^�[�Z�b�^�[
	// �g�p�������e�N�X�`�����擾
	static Texture* GetTexture(const string& _fileName);

	// �g�p���������b�V�����擾
	Mesh* GetMesh(const string& _fileName);
};