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
};

