#pragma once

/*
�摜�̓ǂݍ��݂��s���N���X
*/
class Texture
{
public:
	// �R���X�g���N�^
	Texture();
	// �f�X�g���N�^
	~Texture() {};

	/// <summary>
	/// �e�N�X�`���̃��[�h
	/// </summary>
	/// <param name="_fileName">�e�N�X�`���̃t�@�C����</param>
	/// <returns>true : ���� , false : ���s</returns>
	bool Load(const string& _fileName);

	// ���[�h�����e�N�X�`���̉��
	void Unload();

private:
	// ���̃e�N�X�`����OpenGL ID
	unsigned int mTextureID;
	
	// �e�N�X�`���̉���
	int mWidth;
	// �e�N�X�`���̏c��
	int mHeight;

public:  // �Q�b�^�[�A�Z�b�^�[
	// �e�N�X�`��ID���擾
	int GetTextureID()const { return mTextureID; }
	// �e�N�X�`���̉������擾
	int GetWidth() const { return mWidth; }
	// �e�N�X�`���̏c�����擾
	int GetHeight() const { return mHeight; }
};

