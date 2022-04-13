#pragma once

#define ACTOR_MANAGER ActorManager::mManager

/*
�A�N�^�[�̍X�V���s��(�V���O���g��)
*/
class ActorManager
{
public:
	// �C���X�^���X���쐬����
	static void CreateInstance();
	// �C���X�^���X���폜����
	static void DeleteInstance();

	/// <summary>
	/// �A�N�^�[�̒ǉ�
	/// </summary>
	/// <param name="_actor">�ǉ�����Actor�N���X�̃|�C���^</param>
	void AddActor(Actor* _actor);
	/// <summary>
	/// �A�N�^�[�̍폜
	/// </summary>
	void RemoveActor();
	
	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="_state">�e���͋@��̓��͏��</param>
	void ProcessInput(const InputState& _state);

	/// <summary>
	/// �A�N�^�[�̍X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateActor(float _deltaTime);

	/// <summary>
	/// �V�[�����Ƃ̑S�ẴA�N�^�[�̍폜
	/// </summary>
	/// <param name="_scene">�폜����V�[���̃^�O</param>
	//void RemoveSceneActor(SceneBase::Scene _scene);

	// ���g�̃C���X�^���X
	static ActorManager* mManager;

private:
	// �R���X�g���N�^�A�f�X�g���N�^�̉B��
	ActorManager();
	~ActorManager() {};

	// �S�ẴA�N�^�[���i�[����R���e�i
	vector<Actor*>mActors;
	// Update���ɒǉ����ꂽ�A�N�^�[���ꎞ�I�ɕۑ�����R���e�i
	vector<Actor*>mPendingActors;

	// Update�����ǂ���
	bool mUpdatingActor;
};

