#pragma once

// @@ 2D�̕`�悾���炱�̃N���X�g��Ȃ��\������B���̏ꍇ������
// ���āA�Ȃ�����e�N�X�`���N���X���V���O���g���ɂ���K�v�Ȃ������H

// �O���錾
class Texture;

/*
�X�N���[����ɉ摜�f�[�^��`�悷��N���X
*/
class SpriteComponent :public Component
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����A�N�^�[�̃|�C���^</param>
	/// <param name="_drawOrder">���l���Ⴂ�قǉ����ɕ`�悳���</param>
	SpriteComponent(Actor* _owner, int _drawOrder = 100);
	// �f�X�g���N�^
	~SpriteComponent();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="_shader">�g�p����V�F�[�_�[�N���X�̃|�C���^</param>
	virtual void Draw(Shader* _shader);

protected:
	// Texture*�̃����o�[�ϐ�
	Texture* mTexture;

	// �`�悳��鏇��
	int mDrawOrder;
	// �e�N�X�`���̉���
	int mTexWidth;
	// �e�N�X�`���̏c��
	int mTexHeight;

public:  // �Q�b�^�[�A�Z�b�^�[
	// �`�悳��鏇�Ԃ��擾
	int GetDrawOrder() const { return mDrawOrder; }

	//// @ �����@�����_���[�̒��̃e�N�X�`�����쐬�������ŌĂ�
	//// �e�N�X�`���̉����A�c�����Z�b�g
	//int SetTexSize(int _w, int _h) { mTexWidth = _w; mTexHeight = _h; }
};

