#pragma once

/*
アクターの更新を行う
*/
class ActorManager
{
public:
	// コンストラクタ
	ActorManager();
	// デストラクタ
	~ActorManager() {};

	// インスタンスを作成する
	static void CreateInstance();
	// インスタンスを削除する
	static void DeleteInstance();

	/// <summary>
	/// アクターの追加
	/// </summary>
	/// <param name="_actor">追加するActorクラスのポインタ</param>
	static void AddActor(Actor* _actor);
	/// <summary>
	/// アクターの削除
	/// </summary>
	static void RemoveActor();
	
	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="_state">各入力機器の入力状態</param>
	static void ProcessInput(const InputState& _state);

	/// <summary>
	/// アクターの更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	static void UpdateActor(float _deltaTime);

	/// <summary>
	/// シーンごとの全てのアクターの削除
	/// </summary>
	/// <param name="_scene">削除するシーンのタグ</param>
	//void RemoveSceneActor(SceneBase::Scene _scene);

private:
	// ActorManagerの実体（アプリ内に唯一存在）
	static ActorManager* mManager;

	// 全てのアクターを格納するコンテナ
	vector<Actor*>mActors;
	// Update中に追加されたアクターを一時的に保存するコンテナ
	vector<Actor*>mPendingActors;

	// Update中かどうか
	bool mUpdatingActor;
};

