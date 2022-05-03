#include "pch.h"

Ground::Ground(const Vector3& _pos)
	: Actor(SceneBase::mIsScene,Actor::Tag::eGround)
{
	// Actor�����o�ϐ��̏�����
	SetScale(Vector3(100.0f, 100.0f, 10.0f));
	SetPosition(_pos);
	
	mMeshComponent = new MeshComponent(this);
	mMeshComponent->SetMesh(Renderer::GetMesh("Assets/Actor/Gpmesh/Ground.gpmesh"));
}
