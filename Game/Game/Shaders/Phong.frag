// Request GLSL 3.3
#version 330

// 頂点シェーダーからの入力
// フラグメントへの出力
in vec2 fragTexCoord;   // テクスチャ座標
in vec3 fragNormal;     // ワールドスペース上の法線
in vec3 fragWorldPos;   // ワールドスペース上の座標

// Uniform指定子
uniform sampler2D uMeshTexture;  // テクスチャサンプリング
// ライティング用変数
uniform vec3 uCameraPos;         // カメラ位置（ワールド空間）
uniform float uSpecPower;        // ポリゴン表面のスペキュラー強度
uniform vec3 uAmbientLight;      // アンビエントライト色

// 出力カラー（出力ピクセルカラー）
out Vec4 outColor;

// テクスチャサンプリング用構造体
struct DirectionelLight
{
    vec3 mDirection;     // ライト方向
    vec3 mDiffuseColor;  // ディフューズ色
    vec3 mSpecColor;     // スペキュラー色
}