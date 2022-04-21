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

	// ロードしたシェーダーを削除
	void Unload();

	// シェーダープログラムをアクティブに設定
	void SetActive();

private:
	/// <summary>
	/// シェーダーをコンパイルする
	/// </summary>
	/// <param name="_fileName">コンパイルするシェーダーのファイル名</param>
	/// <param name="_shaderType">シェーダーの種類</param>
	/// <param name="_outShader">シェーダーのIDを格納する参照変数</param>
	/// <returns>true : コンパイル成功 , false : コンパイル失敗</returns>
	bool CompileShader(const string& _fileName, GLenum _shaderType, GLuint& _outShader);

	/// <summary>
	/// シェーダーのコンパイルに成功したかの判定
	/// </summary>
	/// <param name="_shader">シェーダのID</param>
	/// <returns>true : 成功 , false : 失敗</returns>
	bool IsCompiled(GLuint _shader);

	// 頂点/フラグメントプログラムのリンクを確認
	bool IsValidProgram();

	/* シェーダーオブジェクトのIDを格納 */
	// 頂点シェーダー
	GLuint mVertexShader;
	// フラグメントシェーダー
	GLuint mFragShader;
	// シェーダープログラム（頂点シェーダーとフラグメントシェーダーを結合）
	GLuint mShaderProgram;
};