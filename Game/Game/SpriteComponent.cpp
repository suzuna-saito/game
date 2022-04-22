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
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// �l�p�`��`��
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}