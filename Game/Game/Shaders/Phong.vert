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
out vec2 fragTexCoord;          // テクスチャ座標
out vec3 fragNormal;            // ワールドスペース上の法線
out vec3 fragWorldPos;          // ワールドスペース上の座標

void main()
{
    // vec4型に頂点座標を変換
    vec4 pos = vec4(inPosition,1.0);
    // 頂点情報をワールドスペースに変換
    pos = pos * uWorldTransform;
    // フラグメント出力にセット
    fragWorldPos = pos.xyz;
    // クリップ空間にワールド上の頂点座標を変換
    gl_Position = pos * uViewProj;

    // 法線情報をワールドスペースに変換（w = 0）
    fragNormal = (vec4(inNormal, 0.0f) * uWorldTransform).xyz;

    // テクスチャ座標をフラグメントシェーダへ出力
    fragTexCoord = inTexCoord;
    
}