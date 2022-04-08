#include "pch.h"

int main(int argc, char** argv)
{
	// �Q�[���N���X�̒�`
	Game game;
	// �Q�[���N���X�̏�����������������
	bool success = game.Initialize();
	
	// �ŏ��̃V�[����ݒ�
	game.SetFirstScene(new Title(SceneBase::Scene::eTitle));

	if (success)
	{
		game.GameLoop();
	}

	// �Q�[���N���X�̏I������
	game.Termination();

	return 0;
}