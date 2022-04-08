#pragma once

#define OBJECT_MANAGER ObjectManager::mManager

/*
ゲームオブジェクトの更新を行う(シングルトン)
*/
class ObjectManager
{
public:
	// インスタンスを作成する
	static void CreateInstance();
	// インスタンスを削除する
	static void DeleteInstance();

	/// <summary>
	/// オブジェクトの追加
	/// </summary>
	/// <param name="_object">追加するActorクラスのポインタ</param>
	void AddObject(Actor* _object);
	
	/// <summary>
	/// オブジェクトの入力処理
	/// </summary>
	/// <param name="_state">各入力機器の入力状態</param>
	void ProcessInput(const InputState& _state);

	/// <summary>
	/// オブジェクトのアップデート処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateObject(float _deltaTime);

	/// <summary>
	/// オブジェクトの削除
	/// </summary>
	/// <param name="_object">削除するActorクラスのポインタ</param>
	void RemoveObject(Actor* _object);
	/// <summary>
	/// シーンごとの全てのオブジェクトの削除
	/// </summary>
	/// <param name="_scene">削除するシーンのタグ</param>
	void RemoveSceneObject(SceneBase::Scene _scene);

	// 自身のインスタンス
	static ObjectManager* mManager;

private:
	// コンストラクタ、デストラクタの隠蔽
	ObjectManager();
	~ObjectManager() {};

	// 全てのオブジェクトを格納する
	vector<Actor*>mActorObjects;
};

