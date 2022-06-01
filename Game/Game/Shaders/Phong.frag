// Request GLSL 3.3
#version 330

// テクスチャサンプリング用構造体
struct DirectionelLight
{
    vec3 mDirection;     // ライト方向
    vec3 mDiffuseColor;  // ディフューズ色
    vec3 mSpecColor;     // スペキュラー色
}

// 頂点シェーダーからの入力
// フラグメントへの出力
in vec2 fragTexCoord;   // テクスチャ座標
in vec3 fragNormal;     // ワールドスペース上の法線
in vec3 fragWorldPos;   // ワールドスペース上の座標

// Uniform指定子
uniform sampler2D uMeshTexture;      // テクスチャサンプリング
// ライティング用変数
uniform vec3 uCameraPos;             // カメラ位置（ワールド空間）
uniform float uSpecPower;            // ポリゴン表面のスペキュラー強度
uniform vec3 uAmbientLight;          // アンビエントライト色

uniform DirectionalLight uDirLight;  // ディレクショナルライト

// 出力カラー（出力ピクセルカラー）
out Vec4 outColor;

void main()
{
    // 法線とベクトル
    vec3 N = normalize(fragNormal);                 // ポリゴン表面の法線（フラグメントシェーダー上で補間されている）
    vec3 L = normalize(-uDirLight.mDirection);      // ポリゴン表面からライト方向へのベクトル
    vec3 V = normalize(uCameraPos - fragWorldPos);  // ポリゴン表面からカメラ方向へのベクトル
    vec3 R = normalize(reflect(-L,N));              // -L ベクトルを法線 N に対して反射ベクトルRを求める

    // フォン反射計算
    vec3 Phong = uAmbientLight;
    float NdotL = dot(N,L);      // dot = 内積
    
    vec3 Diffuse = uDirLight.mDiffuseColor * max(NdotL,0.0f);
    vec3 Specular = uDirLight.mSpecColor * pow(max(0.0,dot(R,V)),uSpecPower);
    phong += Diffuse + Specular;

    // 最終カラーを出力（alpha = 1）
    outColor = texture(uMeshTexture,fragTexCoord) * vec4(Phong,1.0f);
}