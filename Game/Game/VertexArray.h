#pragma once

/*
���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬���s���N���X
*/
class VertexArray
{
public:
	// ���_���C�A�E�g
	enum class Layout :unsigned char
	{
		//�ʒu&�@��&�e�N�X�`��UV ���������t�H�[�}�b�g
		ePosNormTex,
		//�ʒu&�@��&"�X�L���p�̉e���{�[�����d�ݏ��" & �e�N�X�`��UV 
		ePosNormSkinTex
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_verts">���_�o�b�t�@�̔z��̃|�C���^</param>
	/// <param name="_numVerts">���_��</param>
	/// <param name="_indices">�C���f�b�N�X�o�b�t�@�̔z��̃|�C���^</param>
	/// <param name="_numIndices">�C���f�b�N�X�̐�</param>
	VertexArray(const float* _verts, unsigned int _numVerts,
		const unsigned int* _indices, unsigned int _numIndices);
	// �f�X�g���N�^
	~VertexArray();

	// ���_�z����A�N�e�B�u�ɂ���i�`��o����悤�ɂ���j
	void SetActive();

private:
	// ���_�o�b�t�@�ɂ��钸�_�̐�
	unsigned int mNumVerts;
	// �C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
	unsigned int mNumIndices;
	// ���_�o�b�t�@��OpenGL ID
	unsigned int mVertexBuffer;
	// �C���f�b�N�X�o�b�t�@��OpenGL ID
	unsigned int mIndexBuffer;
	// ���_�z��I�u�W�F�N�g��OpenGL ID
	unsigned int mVertexArray;

public:  // �Q�b�^�[�A�Z�b�^�[
	// �C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐����擾����
	unsigned int GetNumIndices() const { return mNumIndices; }
	// ���_�o�b�t�@�ɂ��钸�_�̐����擾����
	unsigned int GetNumVerts() const { return mNumVerts; }
};

