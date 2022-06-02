#include "pch.h"

MeshComponent::MeshComponent(Actor* _owner, bool _skelton)
	: Component(_owner)
	, mMesh(nullptr)
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
		// ���[���h��ԍ��W�̐ݒ�
		_shader->SetMatrixUniform("uWorldTransform",
			mOwner->GetWorldTransform());

		// ���b�V���ɒ�`����Ă���e�N�X�`�����Z�b�g
		SetTextureToShader(_shader);

		// ���b�V���̒��_�z����A�N�e�B�u�ɂ���
		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();

		// �`�悷��
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void MeshComponent::SetTextureToShader(Shader* _shader)
{
	// ���b�V���e�N�X�`�����Z�b�g
	int texID, TypeCount = 0;
	// �f�B�t���[�Y
	texID = mMesh->GetTextureID(Mesh::TextureType::eDiffuseMap);
	{
		// �e�N�X�`�����Z�b�g���A�A�N�e�B�u�ɂ���
		_shader->SetTexture(GL_TEXTURE0 + TypeCount,GL_TEXTURE_2D, texID);
		// int��uniform��ݒ肷��
		_shader->SetIntUniform("uDiffuseMap", TypeCount);
		++TypeCount;
	}
	// �m�[�}���i�@���j
	texID = mMesh->GetTextureID(Mesh::TextureType::eNormalMap);
	{
		_shader->SetTexture(GL_TEXTURE0 + TypeCount,GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uNormalMap", TypeCount);
		++TypeCount;
	}
	// �X�y�L�����\
	texID = mMesh->GetTextureID(Mesh::TextureType::eSpecularMap);
	{
		_shader->SetTexture(GL_TEXTURE0 + TypeCount,GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uSpecularMap", TypeCount);
		++TypeCount;
	}
	// �G�~�b�V�v
	texID = mMesh->GetTextureID(Mesh::TextureType::eEmissiveMap);
	{
		_shader->SetTexture(GL_TEXTURE0 + TypeCount,GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uEmissiveMap", TypeCount);
	}
}
