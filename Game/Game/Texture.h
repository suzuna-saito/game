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

private:
	// Surface����ϊ����ꂽ�e�N�X�`��
	SDL_Texture* mTex;

	// �e�N�X�`���̉���
	int mWidth;
	// �e�N�X�`���̏c��
	int mHeight;

	// �Q�b�^�[�A�Z�b�^�[
public:
	// @@@
	// Surface����ϊ����ꂽ�e�N�X�`�����擾
	SDL_Texture* GetTexture() const { return mTex; }

	// �e�N�X�`���̉������擾
	int GetWidth() const { return mWidth; }
	// �e�N�X�`���̏c�����擾
	int GetHeight() const { return mHeight; }
};

