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

	// ���[�h�����V�F�[�_�[���폜
	void Unload();

private:
	/// <summary>
	/// �V�F�[�_�[���R���p�C������
	/// </summary>
	/// <param name="_fileName">�R���p�C������V�F�[�_�[�̃t�@�C����</param>
	/// <param name="_shaderType">�V�F�[�_�[�̎��</param>
	/// <param name="_outShader">�V�F�[�_�[��ID���i�[����Q�ƕϐ�</param>
	/// <returns>true : �R���p�C������ , false : �R���p�C�����s</returns>
	bool CompileShader(const string& _fileName, GLenum _shaderType, GLuint& _outShader);

	/// <summary>
	/// �V�F�[�_�[�̃R���p�C���ɐ����������̔���
	/// </summary>
	/// <param name="_shader">�V�F�[�_��ID</param>
	/// <returns>true : ���� , false : ���s</returns>
	bool IsCompiled(GLuint _shader);

	// ���_/�t���O�����g�v���O�����̃����N���m�F
	bool IsValidProgram();

	/* �V�F�[�_�[�I�u�W�F�N�g��ID���i�[ */
	// ���_�V�F�[�_�[
	GLuint mVertexShader;
	// �t���O�����g�V�F�[�_�[
	GLuint mFragShader;
	// �V�F�[�_�[�v���O�����i���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�������j
	GLuint mShaderProgram;

public:  // �Z�b�^�[�A�Q�b�^�[
	// �V�F�[�_�[�v���O�������A�N�e�B�u�ɐݒ�
	void SetActive();

	/// <summary>
	/// �e�N�X�`�����Z�b�g���A�A�N�e�B�u�ɂ���
	/// </summary>
	/// <param name="_texture">�A�N�e�B�u�ɂ���e�N�X�`�����j�b�g</param>
	/// <param name="_target">�e�N�X�`�����o�C���h����Ώ�</param>
	/// <param name="_textureID">�e�N�X�`���̖���</param>
	void SetTexture(GLenum _texture, GLenum _target, GLuint _textureID);

	/// <summary>
	/// int��uniform�ϐ���ݒ肷��
	/// </summary>
	/// <param name="_Name">�ݒ肷��uniform�ϐ���</param>
	/// <param name="_Value">�ݒ肷��int</param>
	void SetIntUniform(const char* _name, const int _value);
	/// <summary>
	/// �s���uniform�ϐ���ݒ肷��
	/// </summary>
	/// <param name="_name">�ݒ肷��uniform�ϐ���</param>
	/// <param name="_matrix">�ݒ肷��s��</param>
	void SetMatrixUniform(const char* _name, const Matrix4& _matrix);
};