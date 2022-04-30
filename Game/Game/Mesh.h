#pragma once

// �O���錾
class Renderer;

/*
���b�V���f�[�^����舵���N���X
*/
class Mesh
{
public:
	// �R���X�g���N�^
	Mesh();
	// �f�X�g���N�^
	~Mesh() {};

	/// <summary>
	/// ���b�V���f�[�^�̓ǂݍ���
	/// </summary>
	/// <param name="_fileName">���[�h���������b�V���̃t�@�C����</param>
	/// <param name="_renderer">Renderer�N���X�̃|�C���^</param>
	/// <returns>true : ���� , false : ���s</returns>
	bool Load(const string& _fileName, Renderer* _renderer);

	// ���[�h�������b�V���f�[�^�̉��
	void Unload();

private:
	// ���b�V���̃e�N�X�`���Q
	vector<Texture*> mTextures;
	// ���b�V���̒��_�z��
	VertexArray* mVertexArray;

	// �V�F�[�_�[�̖��O
	string mShaderName;

	// �I�u�W�F�N�g��Ԃł̋��E���̔��a���L�^
	float mRadius;

	// ���ʔ��ː����̑傫��
	float mSpecPower;
	//// ���Ȕ������x(HDR)
	//float mLuminance;
	//// �����x
	//float mAlpha;

public:  // �Q�b�^�[�A�Z�b�^�[
	// ���̃��b�V���Ɋ��蓖�Ă�ꂽ���_�z����擾
	VertexArray* GetVertexArray() { return mVertexArray; }
	
	// �C���f�b�N�X����e�N�X�`�����擾
	Texture* GetTexture(size_t _index);

	// �V�F�[�_�����擾
	const string& GetShaderName()const { return mShaderName; }

	// �I�u�W�F�N�g��Ԃł̋��E���̔��a���擾
	float GetRadius()const { return mRadius; }
};

