#include "pch.h"

Shader::Shader()
	: mVertexShader(0)
	, mFragShader(0)
	, mShaderProgram(0)
{
}

bool Shader::Load(const string& _vertName, const string& _fragName)
{
	// 頂点シェーダーとフラグメントシェーダーをコンパイルする
	// それぞれのIDをmVertexShader、mFragShaderに保存する
	if (!CompileShader(_vertName, GL_VERTEX_SHADER, mVertexShader) ||
		!CompileShader(_fragName, GL_FRAGMENT_SHADER, mFragShader))
	{
		return false;
	}

	// 頂点/フラグメントシェーダーをリンクして
	// シェーダープログラムを作る
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	// プログラムが正しくリンクされたことを確認
	if (!IsValidProgram())
	{
		return false;
	}

	return true;
}

void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
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
		// コンパイルエラーメッセージを取得
		glGetShaderInfoLog(_shader, 511, nullptr, buffer);
		SDL_Log("GLSLのコンパイルが失敗しました : \n%s", buffer);
		return false;
	}

	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;

	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		// エラーメッセージを取得
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSLのリンクが失敗しました : \n%s", buffer);
		return false;
	}

	return true;
}
