#pragma once

/*
床クラス
*/
class Ground :public Actor
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	Ground(const Vector3& _pos);
	// デストラクタ
	~Ground() {};
};

