#include "pch.h"

MapCreate::MapCreate()
	: mMapSize(Vector2::Zero)
	, mObjDistance(20.0f,20.0f,20.0f)
	, MScale(10.0f)
{
}

MapCreate::~MapCreate()
{
}

bool MapCreate::OpenFile()
{
	// @@@ test
	// �f�[�^�̓ǂݍ���
	if (!ReadTiledJson(mMapDate, "Assets/Config/untitled.json", "test"))
	{
		printf("don't have Layer/test\n");
		return true;
	}

	mMapSize.x = mMapDate[0].size();
	mMapSize.y = mMapDate.size();

	return false;
}

void MapCreate::CreateGround()
{
	// ���s
	for (float iz = 0; iz < mMapSize.y; iz++)
	{
		// ����
		for (float ix = 0; ix < mMapSize.x; ix++)
		{
			// ���蓖�Ă��Ă��鐔��
			const unsigned int name = mMapDate[(int)iz][(int)ix];

			// �|�W�V����
			const Vector3 objPos = Vector3(-mObjDistance.x * ix, mObjDistance.y * iz, 0.0f);
			// �T�C�Y
			const Vector3 objSize = Vector3(MScale, MScale, MScale);

			// ���蓖�Ă��Ă��鐔����1��������
			if (name == 1)
			{
				// ���̐���
			}
		}
	}
}

bool MapCreate::ReadTiledJson(vector<vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	// RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!OpenJsonFile(doc, _fileName))
	{
		return false;
	}
	// �J����document��type��map���H
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}
	// �J����document��layer�͂��邩�H
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}

	// layer�����擾
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	// layer������Y��layer�̓Y�����𒲂ׂ�
	string layerNameString(_layerName);
	int layerIndex = FindLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	// layer���Ƀf�[�^�͂��邩�H
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("date");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", _layerName);
		return false;
	}

	// ���C���[���rapidjson�z��쐬
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	// ���[�U�[�z��m�ہ@�s�����A������̏��ԂɃT�C�Y�m��
	_mapData.resize(height);
	for (auto& mapItr : _mapData)
	{
		mapItr.resize(width);
	}

	// ���[�U�[�z��i�Q�����j�Ƀf�[�^���R�s�[
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//�Ȃ���ID��+1����Ă���̂ŕ␳����
			_mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}

	return true;
}

int MapCreate::FindLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, string& _layerName)
{
	int layerSize = _layer.Size();
	int i;

	string layerNameString(_layerName);

	for (i = 0; i < layerSize; i++)
	{
		string currentLayerName = _layer[i]["name"].GetString();
		// ���݂̃��C���[��(�f�o�b�N)@
		printf("%s\n", currentLayerName.c_str());

		if (layerNameString == currentLayerName)
		{
			break;
		}
	}
	if (i == layerSize)
	{
		return -1;
	}

	return i;
}
