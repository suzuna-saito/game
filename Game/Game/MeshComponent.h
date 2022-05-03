#pragma once

// �O���錾
class Mesh;

/*
���b�V���f�[�^�̊Ǘ��ƕ`����s�Ȃ�
*/
class MeshComponent :public Component
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����A�N�^�[�̃|�C���^�[</param>
	/// <param name="_skelton">�X�P���g���f�[�^��p���邩</param>
	MeshComponent(Actor* _owner, bool _skelton = false);

	// �f�X�g���N�^
	~MeshComponent();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="_shader">�g�p����V�F�[�_�[</param>
	virtual void Draw(Shader* _shader);

protected:
	/// <summary>
	/// �e�N�X�`���^�C�v���ƂɃZ�b�g
	/// </summary>
	/// <param name="_shader">�g�p����V�F�[�_�[�N���X</param>
	void SetTextureToShader(Shader* _shader);

	// ���b�V���f�[�^
	Mesh* mMesh;

	// �X�P���g���f�[�^��p���邩
	bool mSkeltonFlag;

public:  // �Q�b�^�[�A�Z�b�^�[
	// �X�P���g���f�[�^��p���邩�̃t���O���擾
	bool GetIsSkeltal()const { return mSkeltonFlag; }

	// ���b�V���R���|�[�l���g���g��mMesh�̐ݒ�
	virtual void SetMesh(Mesh* _mesh) { mMesh = _mesh; }
};

