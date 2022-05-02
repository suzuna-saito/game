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

VertexArray::VertexArray(const void* _verts, unsigned int _numVerts, const unsigned int* _indices, unsigned int _numIndices,Layout _layout)
	: mNumVerts(_numVerts)
	, mNumIndices(_numIndices)
{
	// ���_�z����쐬
	glGenVertexArrays(1, &mVertexArray);
	// ID��mVertexArray�ɕۑ�
	glBindVertexArray(mVertexArray);

	// ���_���C�A�E�g�� �X�P���^�����f���Ȃ�@�{�[��ID�A�e���x�����T�C�Y���₷
	unsigned vertexSize = 8 * sizeof(float);
	if (_layout == Layout::ePosNormSkinTex)
	{
		vertexSize = 8 * sizeof(float) + 8 * sizeof(char);
	}

	// ���_�o�b�t�@�̍쐬
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	// _verts�𒸓_�o�b�t�@�ɃR�s�[����
	glBufferData(
		GL_ARRAY_BUFFER,						// �o�b�t�@�̎��
		_numVerts * vertexSize * sizeof(float),	// �R�s�[����o�C�g��
		_verts,									// �R�s�[���i�|�C���^�j
		GL_STATIC_DRAW							// ���̃f�[�^�̗��p���@
	);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	// _indices���C���f�b�N�X�o�b�t�@�ɃR�s�[����
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			// �C���f�b�N�X�o�b�t�@�̎w��
		_numIndices * sizeof(unsigned int),	// �f�[�^�̃T�C�Y
		_indices, GL_STATIC_DRAW
	);

	// ���C�A�E�g��PosNormTex�������ꍇ
	if (_layout == Layout::ePosNormTex)
	{
		IfPosNormTex(vertexSize);
	}
	else
	{
		IfPosNormSkinTex(vertexSize);
	}
	
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

void VertexArray::IfPosNormTex(unsigned _vertexSize)
{
	// �ŏ��̒��_������L���ɂ���(�ʒu���W)
	glEnableVertexAttribArray(0);
	// �����̃T�C�Y�A��ށA�t�H�[�}�b�g���w��
	glVertexAttribPointer(
		0,								// ���_�����C���f�b�N�X�i�ʒu���W�j
		3,								// �v�f�̐�
		GL_FLOAT,						// �v�f�̌^
		GL_FALSE,						// �iGL_FLOAT�ɂ͎g��Ȃ��j
		sizeof(float) * _vertexSize,	// �e���_�̃T�C�Y
		0								// ���_�f�[�^�̊J�n�ʒu���炱�̑����܂ł̃I�t�Z�b�g
	);

	//��2�̒��_������L���Ɂi�@���x�N�g���j
	glEnableVertexAttribArray(1);
	// �����̃T�C�Y�A��ށA�t�H�[�}�b�g���w��
	glVertexAttribPointer(
		1,								// ���_�����C���f�b�N�X�i�@���x�N�g���j
		3,								// �v�f�̐�
		GL_FLOAT,						// �v�f�̌^
		GL_FALSE,						// �iGL_FLOAT�ɂ͎g��Ȃ��j
		sizeof(float) * _vertexSize,	// �e���_�̃T�C�Y
		reinterpret_cast<void*>(sizeof(float) * 3)	//�I�t�Z�b�g�|�C���^
	);

	//��3�̒��_������L���Ɂi�e�N�X�`�����W�j
	glEnableVertexAttribArray(2);
	// �����̃T�C�Y�A��ށA�t�H�[�}�b�g���w��
	glVertexAttribPointer(
		2,								// ���_�����C���f�b�N�X�i�e�N�X�`�����W�j
		2,								// �v�f�̐��iUV��2�j
		GL_FLOAT,						// �v�f�̌^
		GL_FALSE,						// �iGL_FLOAT�ɂ͎g��Ȃ��j
		sizeof(float) * _vertexSize,	// �e���_�̃T�C�Y
		reinterpret_cast<void*>(sizeof(float) * 6)	//�I�t�Z�b�g�|�C���^
	);
}

void VertexArray::IfPosNormSkinTex(unsigned _vertexSize)
{
	// float 3���@���@�ʒu x,y,z�@�ʒu�������Z�b�g
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vertexSize, 0);
	// ����float 3�� �� �@�� nx, ny, nz�@�@���������Z�b�g
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _vertexSize,
		reinterpret_cast<void*>(sizeof(float) * 3));
	//�@�e���󂯂�{�[���C���f�b�N�X�ԍ�  (int�^���L�[�v)
	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, _vertexSize,
		reinterpret_cast<void*>(sizeof(float) * 6));
	// �{�[���E�F�C�g��� (float �ɕϊ�)
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, _vertexSize,
		reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
	// ����float 2�� u, v  �e�N�X�`�����W�������Z�b�g
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, _vertexSize,
		reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
}
