#include "pch.h"

Ground::Ground(const Vector3& _pos)
	: Actor(SceneBase::mIsScene,Actor::Tag::eGround)
{
	// Actorメンバ変数の初期化
	mPos = _pos;
	mScale = Vector3(1.0f, 1.0f, 1.0f);
}
