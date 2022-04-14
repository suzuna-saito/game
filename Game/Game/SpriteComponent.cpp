#include "pch.h"

SpriteComponent::SpriteComponent(Actor* _owner, int _drawOrder)
	: Component(_owner)
	, mDrawOrder(_drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw()
{
}
