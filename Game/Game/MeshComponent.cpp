#include "pch.h"

MeshComponent::MeshComponent(Actor* _owner, bool _skelton)
	: Component(_owner)
	, mMesh(nullptr)
	, mTextureIndex(0)
	, mSkeltonFlag(_skelton)
{
	// レンダラーにポインターを送る
	Renderer::AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	// レンダラーからポインタを削除する
	Renderer::RemoveMeshcomponent(this);
}

void MeshComponent::Draw(Shader* _shader)
{
	// メッシュにデータがあるかつ、アクターが更新終了していなければ描画
	if (mMesh && mOwner->GetState() != Actor::State::eDead)
	{

	}
}
