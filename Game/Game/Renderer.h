#pragma once

#define RENDERER Renderer::GetInstance();

/*
�`��i�s���s���N���X
*/
class Renderer
{
public:

	// �C���X�^���X���쐬����
	static void CreateInstance();
	// �C���X�^���X���폜����
	static void DeleteInstance();

	// ����������
	// return true : �����Afalse : ���s
	bool Initialize();
	// �I������
	void Termination();

	// �`�揈��
	void Draw();

private:
	//���g�̃C���X�^���X
	static Renderer* mRenderer;

	//�Q�b�^�[�Z�b�^�[
public:
	/// <summary>
	/// �C���X�^���X���擾����
	/// </summary>
	/// <returns>Renderer�N���X�̃C���X�^���X</returns>
	static Renderer* GetInstance() { return mRenderer; }

};

