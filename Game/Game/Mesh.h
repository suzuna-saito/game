#pragma once

// �O���錾
class Renderer;

/*
���b�V���f�[�^����舵���N���X
*/
class Mesh
{
public:
	union Vertex
	{
		float f;
		uint8_t b[4];
	};

	// �e�N�X�`���^�C�v
	enum class TextureType :unsigned char
	{
		// �f�B�t���[�Y(�x�[�X�J���[)
		eDiffuseMap,
		// �m�[�}��(�@��)
		eNormalMap,
		// �X�y�L����(���ˌ�)
		eSpecularMap,
		// �G�~�b�V�v(���ˌ�)
		eEmissiveMap,
	};

	// �R���X�g���N�^
	Mesh();
	// �f�X�g���N�^
	~Mesh() {};

	/// <summary>
	/// ���b�V���f�[�^�̓ǂݍ���
	/// </summary>
	/// <param name="_fileName">���[�h���������b�V���̃t�@�C����</param>
	/// <param name="_renderer">Renderer�N���X�̃|�C���^</param>
	/// <returns>true : ���� , false : ���s</returns>
	bool Load(const string& _fileName, Renderer* _renderer);

	// ���[�h�������b�V���f�[�^�̉��
	void Unload();

private:
	/// <summary>
	/// �e�N�X�`����ǂݍ���ŁA�^�C�v�ʂɕۑ�
	/// </summary>
	/// <param name="_doc">��̓I�u�W�F�N�g</param>
	void Classification(const rapidjson::Document& _doc);
	/// <summary>
	/// �e�N�X�`���^�C�v��ǂݍ���
	/// </summary>
	/// <param name="_doc">��̓I�u�W�F�N�g</param>
	/// <param name="_texType">�e�N�X�`���^�C�v</param>
	/// <param name="_typeString">�����o��</param>
	/// <returns>�e�N�X�`����ID�iint�^�j</returns>
	int LoadTypeTexture(const rapidjson::Document& _doc, TextureType _texType, const char* _typeString);

	// ���_���C�A�E�g��PosNormTex�������ꍇ�̏���
	void IfPosNormTex(const rapidjson::Value& _vert, vector<Vertex>& _vertices);
	// ���_���C�A�E�g��PosNormSkinTex�������ꍇ�̏���
	void IfPosNormSkinTex(const rapidjson::Value& _vert, vector<Vertex>& _vertices);

	// �e�N�X�`���^�C�v�Ɋ��蓖�Ă�ꂽ�e�N�X�`��
	unordered_map<TextureType, int> mTexturesByType;

	// ���b�V���̃e�N�X�`���Q
	vector<Texture*> mTextures;
	// ���b�V���̒��_�z��
	VertexArray* mVertexArray;

	// �V�F�[�_�[�̖��O
	string mShaderName;

	// �I�u�W�F�N�g��Ԃł̋��E���̔��a���L�^
	float mRadius;

	// ���ʔ��ː����̑傫��
	float mSpecPower;
	//// ���Ȕ������x(HDR)
	//float mLuminance;
	//// �����x
	//float mAlpha;

public:  // �Q�b�^�[�A�Z�b�^�[
	// ���̃��b�V���Ɋ��蓖�Ă�ꂽ���_�z����擾
	VertexArray* GetVertexArray() { return mVertexArray; }
	
	// �C���f�b�N�X����e�N�X�`�����擾
	Texture* GetTexture(size_t _index);

	// �V�F�[�_�����擾
	const string& GetShaderName()const { return mShaderName; }

	// �I�u�W�F�N�g��Ԃł̋��E���̔��a���擾
	float GetRadius()const { return mRadius; }
};

