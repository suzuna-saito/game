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

		// 指定されたタイプのシェーダーを作成
		_outShader = glCreateShader(_shaderType);

		// 読み込んだ文字列でのコンパイルを試みる
		glShaderSource(_outShader, 1, &(contentsChar), nullptr);
		glCompileShader(_outShader);

		// シェーダーが正常にコンパイルされたかどうか
		if (!IsCompiled(_outShader))
		{
			SDL_Log("シェーダー %s のコンパイルに失敗しました", _fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("シェーダーファイル %s が見つかりません", _fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint _shader)
{
	GLint status;

	// コンパイル状態を問い合わせる
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
