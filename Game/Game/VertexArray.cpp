#include "pch.h"

//-------------------------------------------------------------------------------------------------------------------+
// ���_���C�A�E�g
// PosNormTex = 8 * sizeof(float) = 32 bytes
// | �ʒu      | �@��      | Texture|
// | x | y | z | x | y | z | u | v | 
//
// posNormSkinTex
// PosNormSkinTex = (8 * sizeof(float)) + (8 * sizeof(char)) = 40 bytes
// | �ʒu      | �@��       | Bones   | weight  |Texture|
// | x | y | z | x | y | z | char[4] | char[4] | u | v |
//                                    ��weight�̊m�ۂ�char�����A���x���K�v�Ȃ��̂�8bit�Œ菬���Ƃ��Ďg�p����
//-------------------------------------------------------------------------------------------------------------------+

VertexArray::VertexArray(const float* _verts, unsigned int _numVerts, const unsigned int* _indices, unsigned int _numIndices)
	: mNumVerts(_numVerts)
	, mNumIndices(_numIndices)
{
	// ���_�z����쐬
	glGenVertexArrays(1, &mVertexArray);
	// ID��mVertexArray�ɕۑ�
	glBindVertexArray(mVertexArray);

	// ���_�o�b�t�@�̍쐬
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	// _verts�𒸓_�o�b�t�@�ɃR�s�[����
	glBufferData(
		GL_ARRAY_BUFFER,				// �o�b�t�@�̎��
		_numVerts * 8 * sizeof(float),	// �R�s�[����o�C�g��
		_verts,							// �R�s�[���i�|�C���^�j
		GL_STATIC_DRAW					// ���̃f�[�^�̗��p���@
	);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	// _indices���C���f�b�N�X�o�b�t�@�ɃR�s�[����
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			// �C���f�b�N�X�o�b�t�@�̎w��
		_numVerts * sizeof(unsigned int),	// �f�[�^�̃T�C�Y
		_indices, GL_STATIC_DRAW
	);

	// �ŏ��̒��_������L���ɂ���(�ʒu���W)
	glEnableVertexAttribArray(0);

	// �����̃T�C�Y�A��ށA�t�H�[�}�b�g���w��
	glVertexAttribPointer(
		0,					// ���_�����C���f�b�N�X�i�ʒu���W�j
		3,					// �v�f�̐�
		GL_FLOAT,			// �v�f�̌^
		GL_FALSE,			// �iGL_FLOAT�ɂ͎g��Ȃ��j
		sizeof(float) * 8,	// �e���_�̃T�C�Y
		0					// ���_�f�[�^�̊J�n�ʒu���炱�̑����܂ł̃I�t�Z�b�g
	);

	// @@@
	// ���A��O�̒��_������L����
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	// ���p���钸�_�z����w�肷��
	glBindVertexArray(mVertexArray);
}
