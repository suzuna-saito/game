#include "pch.h"

Mesh::Mesh()
	: mVertexArray(nullptr)
	, mRadius(0.0f)
	, mSpecPower(100.0f)
	//, mLuminance(1.0f)
	//, mAlpha(1.0f)
{
	mTexturesByType.emplace(TextureType::eDiffuseMap, 0);
	mTexturesByType.emplace(TextureType::eNormalMap, 0);
	mTexturesByType.emplace(TextureType::eSpecularMap, 0);
	mTexturesByType.emplace(TextureType::eEmissiveMap, 0);
}

bool Mesh::Load(const string& _fileName, Renderer* _renderer)
{
	// �t�@�C���̓ǂݍ���
	ifstream file(_fileName);
	if (!file.is_open())
	{
		printf("�t�@�C����������܂���ł��� : Mesh %s", _fileName.c_str());
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
		printf("Mesh %s �͔�L����json�ł�", _fileName.c_str());
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
		printf("Mesh %s ��textures������܂���", _fileName.c_str());
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
		// �e�N�X�`������̎���diffusemap�̂ݏ������Ă�H
		if (textures.Size() == 1)
		{
			mTexturesByType[TextureType::eDiffuseMap] = t->GetTextureID();
		}
	}

	// �^�C�v�ʃe�N�X�`���ǂݍ���
	Classification(doc);

	// ���_�z��f�[�^�����[�h
	const rapidjson::Value& VertsJson = doc["vertices"];
	if (!VertsJson.IsArray() || VertsJson.Size() < 1)
	{
		printf("Mesh %s ��vertices������܂���", _fileName.c_str());
		return false;
	}

	// �œK�Ƀ��������m�ۂł���悤�A���炩���߃T�C�Y�ύX�̗\����w��
	vector<Vertex> vertices;
	vertices.reserve(VertsJson.Size() * vertSize);

	mRadius = 0.0f;
	for (rapidjson::SizeType i = 0; i < VertsJson.Size(); ++i)
	{
		// ���̂Ƃ����8�̗v�f�Ƃ���
		const rapidjson::Value& Vert = VertsJson[i];
		if (!Vert.IsArray())
		{
			printf("�\�����Ȃ����_�t�H�[�}�b�g�ł� %s", _fileName.c_str());
			return false;
		}
		///////////////////////////////////////////////////////////////////////////////
		Vector3 pos(static_cast<float>(Vert[0].GetDouble()),
			static_cast<float>(Vert[1].GetDouble()),
			static_cast<float>(Vert[2].GetDouble()));

		mRadius = Math::Max(mRadius, pos.LengthSq());

		// ���_���C�A�E�g��PosNormTex�Ȃ�i�{�[�����Ȃ��j
		if (layout == VertexArray::Layout::ePosNormTex)
		{
			IfPosNormTex(Vert, vertices);
		}
		else
		{
			IfPosNormSkinTex(Vert, vertices);
		}
	}

	// ���a��2������
	mRadius = Math::Sqrt(mRadius);

	// �v�f�z��f�[�^�̃��[�h
	const rapidjson::Value& IndJson = doc["indices"];
	if (!IndJson.IsArray() || IndJson.Size() < 1)
	{
		printf("Mesh %s ��indices�͂���܂���", _fileName.c_str());
		return false;
	}

	vector<unsigned int>indices;
	indices.reserve(IndJson.Size() * 3);

	for (rapidjson::SizeType i = 0; i < IndJson.Size(); ++i)
	{
		const rapidjson::Value& Ind = IndJson[i];
		if (!Ind.IsArray() || Ind.Size() != 3)
		{
			printf("�����ȃC���f�b�N�X�ł� %s", _fileName.c_str());
			return false;
		}

		indices.emplace_back(Ind[0].GetUint());
		indices.emplace_back(Ind[1].GetUint());
		indices.emplace_back(Ind[2].GetUint());
	}

	// ������VertexArray�N���X�̍쐬
	mVertexArray = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
		indices.data(), static_cast<unsigned>(indices.size()), layout);

	return true;
}

void Mesh::Unload()
{
}

void Mesh::Classification(const rapidjson::Document& _doc)
{
	// �f�B�t���[�Y
	if (IsExistMember(_doc, "diffusemap"))
	{
		mTexturesByType[TextureType::eDiffuseMap]
			= LoadTypeTexture(_doc, TextureType::eDiffuseMap, "diffusemap");
	}
	// �m�[�}��
	if (IsExistMember(_doc, "normalmap"))
	{
		mTexturesByType[TextureType::eNormalMap]
			= LoadTypeTexture(_doc, TextureType::eNormalMap, "normalmap");
	}
	// �X�y�L����
	if (IsExistMember(_doc, "specularmap"))
	{
		mTexturesByType[TextureType::eSpecularMap]
			= LoadTypeTexture(_doc, TextureType::eSpecularMap, "specularmap");
	}
	// �G�~�b�V�v
	if (IsExistMember(_doc, "emissivemap"))
	{
		mTexturesByType[TextureType::eEmissiveMap]
			= LoadTypeTexture(_doc, TextureType::eEmissiveMap, "emissivemap");
	}
}

int Mesh::LoadTypeTexture(const rapidjson::Document& _doc, TextureType _texType, const char* _typeString)
{
	string noneTexture("none");
	string texName;
	Texture* t;

	texName = _doc[_typeString].GetString();
	if (texName != noneTexture)
	{
		// �g�p�������e�N�X�`�����擾
		t = Renderer::GetTexture(texName);

		// �e�N�X�`�����擾�ł��Ȃ������ꍇ
		if (t == nullptr)
		{
			// �f�t�H���g�̃e�N�X�`�����g�p
			t = Renderer::GetTexture("Assets/Actor/Texture/Default.png");
		}

		return t->GetTextureID();
	}

	return 0;
}

void Mesh::IfPosNormTex(const rapidjson::Value& _vert, vector<Vertex>& _vertices)
{
	Vertex v;
	// float�l��ǉ�
	for (rapidjson::SizeType j = 0; j < _vert.Size(); ++j)
	{
		v.f = static_cast<float>(_vert[j].GetDouble());
		_vertices.emplace_back(v);
	}
}

void Mesh::IfPosNormSkinTex(const rapidjson::Value& _vert, vector<Vertex>& _vertices)
{
	Vertex v;
	// ���_�Ɩ@����ǉ� 6��
	for (rapidjson::SizeType j = 0; j < 6; ++j)
	{
		v.f = static_cast<float>(_vert[j].GetDouble());
		_vertices.emplace_back(v);
	}

	// �X�L�����ǉ��i�{�[���ԍ��Funsigned char��1�o�C�g���j
	// ���[�v�Ƃ��Ă�2��]����@1��]�ڂ̓{�[���ԍ��A2��]�ڂ̓{�[���E�F�C�g��int�Ƃ��Ď���Ă���i�g�p���ɕs������������H�j
	for (rapidjson::SizeType j = 6; j < 14; j += 4)
	{
		v.b[0] = _vert[j].GetUint();
		v.b[1] = _vert[j + 1].GetUint();
		v.b[2] = _vert[j + 2].GetUint();
		v.b[3] = _vert[j + 3].GetUint();
		_vertices.emplace_back(v);
	}

	// �e�N�X�`�����W�ǉ�
	for (rapidjson::SizeType j = 14; j < _vert.Size(); ++j)
	{
		v.f = static_cast<float>(_vert[j].GetDouble());
		_vertices.emplace_back(v);
	}
}

//Texture* Mesh::GetTexture(size_t _index)
//{
//	return nullptr;
//}
