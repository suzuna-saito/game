#pragma once

/*
�V�F�[�_�[�ǂݍ��݃N���X
*/
class Shader
{
public:
	// �R���X�g���N�^
	Shader();
	// �f�X�g���N�^
	~Shader() {};

	/// <summary>
	/// �w�肳�ꂽ���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�̓ǂݍ���
	/// </summary>
	/// <param name="_vertName">���_�V�F�[�_�[��</param>
	/// <param name="_fragName">�t���O�����g�V�F�[�_�[��</param>
	/// <returns> true : ���� , false : ���s</returns>
	bool Load(const string& _vertName, const string& _fragName);

	// �V�F�[�_�[�v���O�������A�N�e�B�u�ɐݒ�
	void SetActive();

	// @@@
};

