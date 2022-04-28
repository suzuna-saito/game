#include "pch.h"

SpriteComponent::SpriteComponent(Actor* _owner, int _drawOrder)
	: Component(_owner)
	, mDrawOrder(_drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	// �X�v���C�g�̒ǉ�
	Renderer::AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	// �X�v���C�g�̍폜
	Renderer::RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* _shader)
{
	if (mTexture)
	{
		// �e�N�X�`���̕��ƍ����ŋ�`���X�P�[�����O
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(mTexWidth),
			static_cast<float>(mTexHeight),
			1.0f);
		// �A�N�^�[�̃��[���h�s��Ɗ|���Ă��̃X�v���C�g�ɕK�v�ȃ��[���h�s������
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();

		// uWorldTransform�̐ݒ�
		_shader->SetMatrixUniform("uWorldTransform", world);

		// �e�N�X�`���̉��n�̐F��ݒ�i���j
		glActiveTexture(GL_TEXTURE0);
		//  �e�N�X�`�����A�N�e�B�u�ɂ���
		glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());

		// ��`��`��
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}
