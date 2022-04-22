#include "pch.h"

SpriteComponent::SpriteComponent(Actor* _owner, int _drawOrder)
	: Component(_owner)
	, mDrawOrder(_drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	// スプライトの追加
	Renderer::AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	// スプライトの削除
	Renderer::RemoveSprite(this);
}

void SpriteComponent::Draw()
{
}
