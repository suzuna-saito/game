#include "pch.h"

MeshComponent::MeshComponent(Actor* _owner, bool _skelton)
	: Component(_owner)
	, mMesh(nullptr)
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
		// ワールド空間座標の設定
		_shader->SetMatrixUniform("uWorldTransform",
			mOwner->GetWorldTransform());

		// メッシュに定義されているテクスチャをセット
		SetTextureToShader(_shader);

		// メッシュの頂点配列をアクティブにする
		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();

		// 描画する
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void MeshComponent::SetTextureToShader(Shader* _shader)
{
	// メッシュテクスチャをセット
	int texID, TypeCount = 0;
	// ディフューズ
	texID = mMesh->GetTextureID(Mesh::TextureType::eDiffuseMap);
	{
		// テクスチャをセットし、アクティブにする
		_shader->SetTexture(GL_TEXTURE0 + TypeCount,GL_TEXTURE_2D, texID);
		// intのuniformを設定する
		_shader->SetIntUniform("uDiffuseMap", TypeCount);
		++TypeCount;
	}
	// ノーマル（法線）
	texID = mMesh->GetTextureID(Mesh::TextureType::eNormalMap);
	{
		_shader->SetTexture(GL_TEXTURE0 + TypeCount,GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uNormalMap", TypeCount);
		++TypeCount;
	}
	// スペキュラ―
	texID = mMesh->GetTextureID(Mesh::TextureType::eSpecularMap);
	{
		_shader->SetTexture(GL_TEXTURE0 + TypeCount,GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uSpecularMap", TypeCount);
		++TypeCount;
	}
	// エミッシプ
	texID = mMesh->GetTextureID(Mesh::TextureType::eEmissiveMap);
	{
		_shader->SetTexture(GL_TEXTURE0 + TypeCount,GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uEmissiveMap", TypeCount);
	}
}
