#include "pch.h"

Shader::Shader()
	: mVertexShader(0)
	, mFragShader(0)
	, mShaderProgram(0)
{
}

bool Shader::Load(const string& _vertName, const string& _fragName)
{
	// ���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[���R���p�C������
	// ���ꂼ���ID��mVertexShader�AmFragShader�ɕۑ�����
	if (!CompileShader(_vertName, GL_VERTEX_SHADER, mVertexShader) ||
		!CompileShader(_fragName, GL_FRAGMENT_SHADER, mFragShader))
	{
		return false;
	}

	// ���_/�t���O�����g�V�F�[�_�[�������N����
	// �V�F�[�_�[�v���O���������
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	// �v���O�����������������N���ꂽ���Ƃ��m�F
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
		// �R���p�C���G���[���b�Z�[�W���擾
		glGetShaderInfoLog(_shader, 511, nullptr, buffer);
		SDL_Log("GLSL�̃R���p�C�������s���܂��� : \n%s", buffer);
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
		// �G���[���b�Z�[�W���擾
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL�̃����N�����s���܂��� : \n%s", buffer);
		return false;
	}

	return true;
}
