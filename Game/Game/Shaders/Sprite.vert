//-------------------------------------------------------------------------------------------+
// スプライト(2D)用頂点シェーダ
//-------------------------------------------------------------------------------------------+

// Request GLSL 3.3
#version 330

// アトリビュート (バッファのAttribPointerで指定したデータ)
layout(location = 0) in vec3 inPosition;  // 頂点座標
layout(location = 1) in vec3 inNormal;    // 法線
layout(location = 2) in vec2 inTexCoord;  // テクスチャ座標(UV)

// Uniform指定子
uniform mat4 uWorldTransform;   // ワールド変換行列
uniform mat4 uViewProj;         // ビュー * プロジェクションの合成行列

// フラグメントシェーダへの出力
out vec2 fragTexCoord;

void main()
{
	// 頂点座標をgl_Position用にvec4型へ変換
	vec4 pos = vec4(inPosition, 1.0);
	// クリップ空間にワールド座標を変換
	gl_Position = pos * uWorldTransform * uViewProj;

	// テクスチャ座標をフラグメントへ出力
	fragTexCoord = inTexCoord;
}