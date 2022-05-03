#include "pch.h"

Ground::Ground(const Vector3& _pos)
	: Actor(SceneBase::mIsScene,Actor::Tag::eGround)
{
	// Actorメンバ変数の初期化
	SetScale(Vector3(100.0f, 100.0f, 10.0f));
	SetPosition(_pos);
	
	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(Renderer::GetMesh("Assets/Actor/Gpmesh/Ground.gpmesh"));
}
