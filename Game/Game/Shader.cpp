#include "pch.h"

Shader::Shader()
{
}

bool Shader::Load(const string& _vertName, const string& _fragName)
{
	return false;
}

void Shader::SetActive()
{
}

bool Shader::CompileShader(const string& _fileName, GLenum _shaderType, GLuint& _outShader)
{
	// �t�@�C���ǂݍ���
	ifstream shaderFile(_fileName);
	// �t�@�C�����J��
	if (shaderFile.is_open())
	{
		// ���ׂẴe�L�X�g��1�̕�����ɓǂݍ���
		stringstream sstream;
		sstream << shaderFile.rdbuf();
		string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		// �w�肳�ꂽ�^�C�v�̃V�F�[�_�[���쐬
		_outShader = glCreateShader(_shaderType);

		// �ǂݍ��񂾕�����ł̃R���p�C�������݂�
		glShaderSource(_outShader, 1, &(contentsChar), nullptr);
		glCompileShader(_outShader);

		// �V�F�[�_�[������ɃR���p�C�����ꂽ���ǂ���
		if (!IsCompiled(_outShader))
		{
			SDL_Log("�V�F�[�_�[ %s �̃R���p�C���Ɏ��s���܂���", _fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("�V�F�[�_�[�t�@�C�� %s ��������܂���", _fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint _shader)
{
	GLint status;

	// �R���p�C����Ԃ�₢���킹��
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
	}

	return true;
}

bool Shader::IsValidProgram()
{
	return false;
}
