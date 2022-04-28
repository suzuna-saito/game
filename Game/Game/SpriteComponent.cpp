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

void SpriteComponent::Draw(Shader* _shader)
{
	if (mTexture)
	{
		// テクスチャの幅と高さで矩形をスケーリング
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(mTexWidth),
			static_cast<float>(mTexHeight),
			1.0f);
		// アクターのワールド行列と掛けてこのスプライトに必要なワールド行列を作る
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();

		// uWorldTransformの設定
		_shader->SetMatrixUniform("uWorldTransform", world);

		// テクスチャの下地の色を設定（白）
		glActiveTexture(GL_TEXTURE0);
		//  テクスチャをアクティブにする
		glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());

		// 矩形を描画
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}
