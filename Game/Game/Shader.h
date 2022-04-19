#pragma once

/*
シェーダー読み込みクラス
*/
class Shader
{
public:
	// コンストラクタ
	Shader();
	// デストラクタ
	~Shader() {};

	/// <summary>
	/// 指定された頂点シェーダーとフラグメントシェーダーの読み込み
	/// </summary>
	/// <param name="_vertName">頂点シェーダー名</param>
	/// <param name="_fragName">フラグメントシェーダー名</param>
	/// <returns> true : 成功 , false : 失敗</returns>
	bool Load(const string& _vertName, const string& _fragName);

	// シェーダープログラムをアクティブに設定
	void SetActive();

	// @@@
};

