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
	}

	return true;
}

bool Shader::IsCompiled(GLuint _shader)
{
	return false;
}

bool Shader::IsValidProgram()
{
	return false;
}
