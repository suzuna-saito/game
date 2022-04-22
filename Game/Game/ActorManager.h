#pragma once

/*
�A�N�^�[�̍X�V���s��
*/
class ActorManager
{
public:
	// �R���X�g���N�^
	ActorManager();
	// �f�X�g���N�^
	~ActorManager() {};

	// �C���X�^���X���쐬����
	static void CreateInstance();
	// �C���X�^���X���폜����
	static void DeleteInstance();

	/// <summary>
	/// �A�N�^�[�̒ǉ�
	/// </summary>
	/// <param name="_actor">�ǉ�����Actor�N���X�̃|�C���^</param>
	static void AddActor(Actor* _actor);
	/// <summary>
	/// �A�N�^�[�̍폜
	/// </summary>
	static void RemoveActor();
	
	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="_state">�e���͋@��̓��͏��</param>
	static void ProcessInput(const InputState& _state);

	/// <summary>
	/// �A�N�^�[�̍X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	static void UpdateActor(float _deltaTime);

	/// <summary>
	/// �V�[�����Ƃ̑S�ẴA�N�^�[�̍폜
	/// </summary>
	/// <param name="_scene">�폜����V�[���̃^�O</param>
	//void RemoveSceneActor(SceneBase::Scene _scene);

private:
	// ActorManager�̎��́i�A�v�����ɗB�ꑶ�݁j
	static ActorManager* mManager;

	// �S�ẴA�N�^�[���i�[����R���e�i
	vector<Actor*>mActors;
	// Update���ɒǉ����ꂽ�A�N�^�[���ꎞ�I�ɕۑ�����R���e�i
	vector<Actor*>mPendingActors;

	// Update�����ǂ���
	bool mUpdatingActor;
};

