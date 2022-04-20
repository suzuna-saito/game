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
	// ファイル読み込み
	ifstream shaderFile(_fileName);
	// ファイルを開く
	if (shaderFile.is_open())
	{
		// すべてのテキストを1つの文字列に読み込む
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
