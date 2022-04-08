#pragma once

/*
�e�V�[���̊��N���X
*/
class SceneBase
{
public:
	// �R���X�g���N�^
	SceneBase();
	// �f�X�g���N�^
	~SceneBase() {};

	// ���t���[���̓��͏���
	virtual void Input(const InputState& _state) = 0;

	// ���t���[���̍X�V����
	virtual SceneBase* Update() = 0;

	// �V�[���̃^�O�i��ށj
	enum class Scene :unsigned char
	{
		// ������
		eInit,
		// �^�C�g��
		eTitle,
		// @@@ end
		eEnd,
	};

	// ���݂̃V�[���^�O
	static Scene mIsScene;

protected:
	// ���̃V�[���ɑJ�ڂ��邩
	// true : ���� false : ���Ȃ�
	bool mSceneTransitionFlag;

};

