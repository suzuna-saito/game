#pragma once

/*
�^�C�g���V�[���̃N���X
*/
class Title :public SceneBase
{
public:
	// �R���X�g���N�^
	Title(const Scene& _nowScene);
	// �f�X�g���N�^
	~Title();

	// ���t���[���̓��͏���
	void Input(const InputState& _state) override;

	// ���t���[���̍X�V����
	SceneBase* Update() override;
};

