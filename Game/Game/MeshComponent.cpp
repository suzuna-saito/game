#include "pch.h"

MeshComponent::MeshComponent(Actor* _owner, bool _skelton)
	: Component(_owner)
	, mMesh(nullptr)
	, mTextureIndex(0)
	, mSkeltonFlag(_skelton)
{
	// �����_���[�Ƀ|�C���^�[�𑗂�
	Renderer::AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	// �����_���[����|�C���^���폜����
	Renderer::RemoveMeshcomponent(this);
}

void MeshComponent::Draw(Shader* _shader)
{
	// ���b�V���Ƀf�[�^�����邩�A�A�N�^�[���X�V�I�����Ă��Ȃ���Ε`��
	if (mMesh && mOwner->GetState() != Actor::State::eDead)
	{

	}
}
