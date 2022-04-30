#include "pch.h"

Mesh::Mesh()
	: mVertexArray(nullptr)
	, mRadius(0.0f)
	, mSpecPower(100.0f)
	//, mLuminance(1.0f)
	//, mAlpha(1.0f)
{
}

bool Mesh::Load(const string& _fileName, Renderer* _renderer)
{
	// �t�@�C���̓ǂݍ���
	ifstream file(_fileName);
	if (!file.is_open())
	{
		SDL_Log("�t�@�C����������܂���ł��� : Mesh %s", _fileName.c_str());
		return false;
	}

	// filestream�Ƀt�@�C�����������荞��
	stringstream fileStream;
	fileStream << file.rdbuf();
	string contents = fileStream.str();
	// �t�@�C���������json������ɕϊ�
	rapidjson::StringStream jsonStr(contents.c_str());
	// ��̓I�u�W�F�N�g�쐬
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	// JSON�I�u�W�F�N�g���H
	if (!doc.IsObject())
	{
		SDL_Log("Mesh %s �͔�L����json�ł�", _fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// �o�[�W�����`�F�b�N
	if (ver != 1)
	{
		printf("Mesh %s �̓o�[�W������1�ł͂���܂���", _fileName.c_str());
		return false;
	}

	mShaderName = doc["shader"].GetString();

	// ���_���C�A�E�g�ƃT�C�Y���t�@�C������Z�b�g
	VertexArray::Layout layout = VertexArray::Layout::ePosNormTex;
	size_t vertSize = 8;

	string vertexFormat = doc["vertexformat"].GetString();
	if (vertexFormat == "PosNormSkinTex")
	{
		layout = VertexArray::Layout::ePosNormSkinTex;
		// ����� "Vertex "���j�I���̐��ł�, which is 8 + 2 (for skinning)s�@1�̒��_�̏W���̐��@�W�@�{�@�Q�i�X�L�j���O���j
		// 3 (�ʒuxyz) + 3(�@��xyz) + 2(Bone�Əd�݁j�{�@2(UV)  �̌v�@10���i40byte) �@
		vertSize = 10;
	}

	// �e�N�X�`���̃��[�h
	const rapidjson::Value& textures = doc["textures"];
	if (!textures.IsArray() || textures.Size() < 1)
	{
		SDL_Log("Mesh %s �Ƀe�N�X�`��������܂���", _fileName.c_str());
		return false;
	}

	// �X�y�L�������x
	mSpecPower = static_cast<float>(doc["specularPower"].GetDouble());

	//@@@ �G�~�b�V�v���ĂȂ񂼁B�X�y�L�������ĂȂ�
	//// �G�~�b�V�v���x�l(��`����Ă����)
	//if (IsExistMember(doc, "luminance"))
	//{
	//	mLuminance = ForceGetFloat(doc["luminance"]);
	//}

	//// �����x
	//if (IsExistMember(doc, "alpha"))
	//{
	//	mAlpha = ForceGetFloat(doc["alpha"]);
	//}

	for (rapidjson::SizeType i = 0; i < textures.Size(); ++i)
	{
		// ���łɃ��[�h����ăe�N�X�`������Ȃ������ׂ�
		string texName = textures[i].GetString();
		Texture* t = _renderer->GetTexture(texName);
		// �e�N�X�`�����擾�ł��Ȃ������ꍇ
		if (t == nullptr)
		{
			// �f�t�H���g�̃e�N�X�`�����g�p
			t = _renderer->GetTexture("Assets/Actor/Texture/Default.png");
		}
		// ���b�V���̃e�N�X�`���Q�ɒǉ�
		mTextures.emplace_back(t);

		// @@@�@�H�H�H
		if (textures.Size() == 1)
		{
			
		}
	}

	if(IsExistMember())

	return true;
}

void Mesh::Unload()
{
}

Texture* Mesh::GetTexture(size_t _index)
{
	return nullptr;
}
