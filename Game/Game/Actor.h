#pragma once

/*
全てのActorの基底クラス
*/
class Actor
{
public:
	// アクターの状態管理用タグ
	enum class State :unsigned char
	{
		// アクティブ
		eActive,
		// 更新停止
		ePaused,
		// 更新終了
		eDead,
	};

	// アクターの種類判別タグ
	enum class Tag :unsigned char
	{
		// 床
		eGround,
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_nowScene">生成された時のシーン</param>
	/// <param name="_actorTag">アクターのタグ</param>
	Actor(const SceneBase::Scene& _nowScene, const Tag& _actorTag);
	// デストラクタ
	virtual ~Actor() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void Update(float _deltaTime);

	/// <summary>
	/// アクターがもつ全コンポーネントを更新
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateComponents(float _deltaTime);

	/// <summary>
	/// 入力状態を受け取りActorとComponentの入力更新関数を呼び出す
	/// </summary>
	/// <param name="_keyState">各入力機器の入力状態</param>
	void ProcessInput(const InputState& _keyState);

	/// <summary>
	/// アクター独自の入力情報を変数に保存しUpdateActorで更新を行う
	/// </summary>
	/// <param name="_keyState">各入力機器の入力状態</param>
	virtual void ActorInput(const InputState& _keyState) {};

	/// <summary>
	/// アクター独自の更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	virtual void UpdateActor(float _deltaTime) = 0;

	// 個々の変換行列を作成
	void ComputeWorldTransform();

protected:
	// 各自のアクターの状態
	State mState;

	// @@@
	// Transform
	Vector3 mPos;
	Vector3 mScale;
	Quaternion mRotation;

	// アクターのワールド行列
	Matrix4 mWorldTransform;
	// ワールド行列の再計算の必要性を管理
	bool mRecomputeWorldTransform;

	// 各自のアクターが持つコンポーネント
	vector<Component*>mComponents;

private:
	// 各自のアクターを生成したシーン
	SceneBase::Scene mDirthplaceScene;
	// 各自のアクターが持つタグ
	Tag mTag;

public:  // ゲッター、セッター
	// アクターが生成された時のシーンを取得
	SceneBase::Scene GetScene()const { return mDirthplaceScene; }

	// アクターの状態を取得
	State GetState()const { return mState; }

	// アクターのポジションを取得
	const Vector3& GetPosition()const { return mPos; }
	// アクターの向きを取得
	const Quaternion& GetRotation()const { return mRotation; }

	// アクターのワールド行列を取得
	const Matrix4& GetWorldTransform()const { return mWorldTransform; }

	// アクターの前方を表すベクトルを取得
	Vector3 GetForward()const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	// アクターのポジションをセット(mRecomputeWorldTransformをtrueにする)
	void SetPosition(const Vector3& _pos) { mPos = _pos; mRecomputeWorldTransform = true; }
	// アクターの向きをセット(mRecomputeWorldTransformをtrueにする)
	void SetRotation(const Quaternion& _qotation) { mRotation = _qotation; mRecomputeWorldTransform = true; }
};

