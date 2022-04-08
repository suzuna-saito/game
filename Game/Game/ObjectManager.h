#pragma once

#define OBJECT_MANAGER ObjectManager::mManager

/*
�Q�[���I�u�W�F�N�g�̍X�V���s��(�V���O���g��)
*/
class ObjectManager
{
public:
	// �C���X�^���X���쐬����
	static void CreateInstance();
	// �C���X�^���X���폜����
	static void DeleteInstance();

	/// <summary>
	/// �I�u�W�F�N�g�̒ǉ�
	/// </summary>
	/// <param name="_object">�ǉ�����Actor�N���X�̃|�C���^</param>
	void AddObject(Actor* _object);
	
	/// <summary>
	/// �I�u�W�F�N�g�̓��͏���
	/// </summary>
	/// <param name="_state">�e���͋@��̓��͏��</param>
	void ProcessInput(const InputState& _state);

	/// <summary>
	/// �I�u�W�F�N�g�̃A�b�v�f�[�g����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateObject(float _deltaTime);

	/// <summary>
	/// �I�u�W�F�N�g�̍폜
	/// </summary>
	/// <param name="_object">�폜����Actor�N���X�̃|�C���^</param>
	void RemoveObject(Actor* _object);
	/// <summary>
	/// �V�[�����Ƃ̑S�ẴI�u�W�F�N�g�̍폜
	/// </summary>
	/// <param name="_scene">�폜����V�[���̃^�O</param>
	void RemoveSceneObject(SceneBase::Scene _scene);

	// ���g�̃C���X�^���X
	static ObjectManager* mManager;

private:
	// �R���X�g���N�^�A�f�X�g���N�^�̉B��
	ObjectManager();
	~ObjectManager() {};

	// �S�ẴI�u�W�F�N�g���i�[����
	vector<Actor*>mActorObjects;
};

