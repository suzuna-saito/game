#include "pch.h"

Ground::Ground(const Vector3& _pos)
	: Actor(SceneBase::mIsScene,Actor::Tag::eGround)
{
	// Actorƒƒ“ƒo•Ï”‚Ì‰Šú‰»
	mPos = _pos;
	mScale = Vector3(1.0f, 1.0f, 1.0f);


}
